#include "../../includes/cub3d.h"
#include "../../includes/map.h"

// FONCTION POUR METTRE LES TEXTURES SUR LES MURS				<-------
static void	walls_texture(float ray_a, t_rays *r)
{
	if (r->cross == 'v')					// faces W et E
	{
		if (ray_a > 90 && ray_a < 270)		// W
			r->color = CV1;
		else								// E
			r->color = CV2;
	}
	else									// faces N et S
	{
		if (ray_a > 0 && ray_a < 180)		// N
			r->color = CH1;
		else								// S
			r->color = CH2;
	}
}

static void	ray_transfo(t_game *game, t_rays *r)
{
	r->dist *= fix_fisheye(game->m.player_angle - game->m.a_rad);
	r->top = game->world_h * game->m.m_size / r->dist;
	if (r->top > game->world_h)
		r->top = game->world_h;
	r->bot = (game->world_h / 2) - (r->top / 2);
	r->lpr = game->width / M_2RAYS;
	r->l = -1;
	walls_texture(game->m.a_deg, r);
}

// l = line | lpr = lines per ray | bot = wall bottom | top = wall top
static void	draw_3d(t_game *game, t_rays *r)
{
	static int	x = 0;

	ray_transfo(game, r);
	walls_texture(game->m.a_deg, r);
	while (++r->l < r->lpr)
	{
		r->p_y = -1;
		while (++r->p_y < r->bot)
			my_mlx_pixel_put(&game->world, x + r->l, r->p_y, game->m.c_ceil);				// plafond
		r->p_y = -1;
		while (++r->p_y < r->top)
		{
			my_mlx_pixel_put(&game->world, x + r->l, r->p_y + r->bot, r->color);			// walls
		}
		r->p_y = -1;
		r->shift = r->top + r->bot;
		while (++r->p_y < game->world_h)
			my_mlx_pixel_put(&game->world, x + r->l, r->p_y + r->shift, game->m.c_floor);	// sol
	}
	x += r->lpr;
	if (r->rays == M_2RAYS - 1)
		x = 0;
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
		// draw_ray(&game->map, &game->m, &r, RED);						// à enlever plus tard
		game->m.a_rad -=  M_05_DEG_RAD;
		check_angle(game->m.a_rad, &game->m.a_deg);
	}
	game->m.pos_x -= M_HALF_PLAYER;
	game->m.pos_y -= M_HALF_PLAYER;
	game->m.a_rad += M_RAYS * M_05_DEG_RAD;
	game->m.a_deg = rad_to_deg(game->m.a_rad);
}
