#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	draw_v_line(t_image *image, t_rays *r, int color)
{
	double	d_x;
	double	d_y;
	int		pix;
	double	p_x;
	double	p_y;

	d_x = 0;
	d_y = r->y2 - r->y1;
	pix = sqrt((d_x * d_x) + (d_y * d_y));
	d_x /= pix;
	d_y /= pix;
	p_x = r->ix;
	p_y = r->y1;
	while (pix)
	{
		my_mlx_pixel_put(image, p_x, p_y, color);
		p_x += d_x;
		p_y += d_y;
		--pix;
	}
}

static void	walls_texture(float ray_a, t_rays *r)
{
	if (r->cross == 'v')					// faces W et E
	{
		if (ray_a > 90 && ray_a < 270)		// W
			r->tex = &r->tex_w;
			// r->color = CV1;
		else								// E
			r->tex = &r->tex_e;
			// r->color = CV2;
	}
	else									// faces N et S
	{
		if (ray_a > 0 && ray_a < 180)		// N
			r->tex = &r->tex_n;
			// r->color = CH1;
		else								// S
			r->tex = &r->tex_s;
			// r->color = CH2;
	}
}

static void	ray_transfo(t_game *game, t_rays *r)
{
	r->dist *= fix_fisheye(game->m.player_angle - game->m.a_rad);
	walls_texture(game->m.a_deg, r);
	r->w_bot = game->world_h * game->m.m_size / r->dist;
	r->ty_step = r->tex->heigth / r->w_bot;
	r->to = 0;
	if (r->w_bot > game->world_h)
	{
		r->to = (r->w_bot - game->world_h) / 2;
		r->w_bot = game->world_h;
	}
	r->w_top = (game->world_h / 2) - (r->w_bot / 2);
	r->lpr_cpy = game->width / M_2RAYS + 1;
}

static void	draw_3d(t_game *game, t_rays *r)
{
	ray_transfo(game, r);
	r->lpr = r->lpr_cpy;
	while (--r->lpr)
	{
		r->y1 = 0;
		r->y2 = r->w_top;
		draw_v_line(&game->world, r, game->m.c_ceil);
		r->iy = -1;
		r->ty = r->to * r->ty_step;
		if (r->cross == 'h')
			r->tx = (int)(r->x * r->lpr_cpy) % r->tex->width;
		else
			r->tx = (int)(r->y * r->lpr_cpy) % r->tex->width;
		while (++r->iy < r->w_bot)
		{
			r->c = get_tex_color(r->tex, r->tx, r->ty);
			my_mlx_pixel_put(&game->world, r->ix, r->iy + r->w_top, r->c);
			r->ty += r->ty_step;
		}
		r->y1 =  r->w_bot + r->w_top;
		r->y2 = game->world_h;
		draw_v_line(&game->world, r, game->m.c_floor);
		r->ix++;
	}
}

// utiliser M_05_DEG_RAD pour projeter 120 rayons
// utiliser M_1_DEG_RAD pour projet 60 rayons
// sans oublier d'adapter les M_HALF_RAYS / M_RAYS / M_2RAYS
void	raycasting(t_game *game)
{
	game->m.pos_x += M_HALF_PLAYER;
	game->m.pos_y += M_HALF_PLAYER;
	game->m.player_angle = game->m.a_rad;
	game->m.a_rad += M_RAYS * M_05_DEG_RAD;
	check_angle(game->m.a_rad, &game->m.a_deg);
	game->r.rays = -1;
	game->r.ix = 0;
	while (++game->r.rays < M_2RAYS)
	{
		game->r.dist_v = 0;
		game->r.dist_h = 0;
		game->r.atan = -1 / tan(-game->m.a_rad);
		game->r.ntan = -tan(-game->m.a_rad);
		ray_horizontal_check(&game->m, &game->r);
		ray_vertical_check(&game->m, &game->r);
		compare_dist(&game->r);
		draw_3d(game, &game->r);
		// draw_ray(&game->map, &game->m, &r, RED);
		game->m.a_rad -=  M_05_DEG_RAD;
		check_angle(game->m.a_rad, &game->m.a_deg);
	}
	game->m.pos_x -= M_HALF_PLAYER;
	game->m.pos_y -= M_HALF_PLAYER;
	game->m.a_rad += M_RAYS * M_05_DEG_RAD;
	game->m.a_deg = rad_to_deg(game->m.a_rad);
}
