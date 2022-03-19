#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void wall_texture(t_game *game, t_rays *r)
{
	r->iy = -1;
	r->ty = r->to * r->ty_step;
	if (r->cross == 'h')
	{
		r->tx = (int)((r->wx - (int)r->wx) * r->tex->width);
		if (game->m.a_deg > 180)
			r->tx = r->tex->width - r->tx - 1;
	}
	else
	{
		r->tx = (int)((r->wy - (int)r->wy) * r->tex->width);
		if (game->m.a_deg > 90 && game->m.a_deg < 270)
			r->tx = r->tex->width - r->tx - 1;
	}
	while (++r->iy < r->w_bot)
	{
		r->c = get_tex_color(r->tex, r->tx, r->ty);
		my_mlx_pixel_put(&game->world, r->ix, r->iy + r->w_top, r->c);
		r->ty += r->ty_step;
	}
}

static void	use_textures(t_game *game, t_rays *r)
{
	while (--r->lpr)
	{
		r->y1 = 0;
		r->y2 = r->w_top;
		draw_v_line(&game->world, r, game->m.c_ceil);
		wall_texture(game, r);
		r->y1 = r->w_bot + r->w_top;
		r->y2 = game->world_h;
		draw_v_line(&game->world, r, game->m.c_floor);
		r->ix++;
	}
}

static void	use_color(t_game *game, t_rays *r)
{
	while (--r->lpr)
	{
		r->y1 = 0;
		r->y2 = r->w_top;
		draw_v_line(&game->world, r, game->m.c_ceil);
		r->iy = -1;
		while (++r->iy < r->w_bot)
			my_mlx_pixel_put(&game->world, r->ix, r->iy + r->w_top, r->c);
		r->y1 =  r->w_bot + r->w_top;
		r->y2 = game->world_h;
		draw_v_line(&game->world, r, game->m.c_floor);
		r->ix++;
	}
}

static void	ray_to_3d(t_game *game, t_rays *r)
{
	r->dist *= fix_fisheye(game->m.player_angle - game->m.a_rad);
	r->w_bot = game->world_h * game->m.m_size / r->dist;
	r->tex = ray_texture(game->m.a_deg, r);
	if (r->tex)
	{
		r->ty_step = r->tex->heigth / r->w_bot;
		r->to = 0;
	}
	else
		r->c = ray_color(game->m.a_deg, r);
	if (r->w_bot > game->world_h)
	{
		if (r->tex)
			r->to = (r->w_bot - game->world_h) / 2;
		r->w_bot = game->world_h;
	}
	r->w_top = (game->world_h / 2) - (r->w_bot / 2);
	r->lpr_cpy = (game->width / r->r_1) + 1;
	r->lpr = r->lpr_cpy;
	if (r->tex)
		use_textures(game, r);
	else 
		use_color(game, r);
}

// pour voir les rayons dans la minimap, ajouté après draw_3d() :
// draw_ray(&game->map, &game->m, &game->r, RED);
void	raycasting(t_game *game)
{
	game->m.pos_x += M_HALF_PLAYER;
	game->m.pos_y += M_HALF_PLAYER;
	game->m.player_angle = game->m.a_rad;
	game->m.a_rad += game->r.fov_05;
	check_angle(game->m.a_rad, &game->m.a_deg);
	game->r.rays = -1;
	game->r.ix = 0;
	while (++game->r.rays < game->r.r_1)
	{
		game->r.dist_v = 0;
		game->r.dist_h = 0;
		game->r.atan = -1 / tan(-game->m.a_rad);
		game->r.ntan = -tan(-game->m.a_rad);
		game->r.spe = '0';
		ray_horizontal_check(&game->m, &game->r);
		ray_vertical_check(&game->m, &game->r);
		compare_rays(game);
		ray_to_3d(game, &game->r);
		game->m.a_rad -=  game->r.r_ra;
		check_angle(game->m.a_rad, &game->m.a_deg);
	}
	game->m.pos_x -= M_HALF_PLAYER;
	game->m.pos_y -= M_HALF_PLAYER;
	game->m.a_rad += game->r.fov_05;
	game->m.a_deg = rad_to_deg(game->m.a_rad);
}
