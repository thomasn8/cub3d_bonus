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
		r->x1 = x + r->l;
		r->y1 = 0;
		r->x2 = x + r->l;
		r->y2 = r->bot;
		draw_lines(&game->world, r, game->m.c_ceil);			// plafond
		r->x1 = x + r->l;
		r->y1 = r->bot;
		r->x2 = x + r->l;
		r->y2 = r->top + r->bot;
		draw_lines(&game->world, r, r->color);					// walls
		r->x1 = x + r->l;
		r->y1 = r->top + r->bot;
		r->x2 = x + r->l;
		r->y2 = game->world_h;
		draw_lines(&game->world, r, game->m.c_floor);			// sol
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
	t_rays	r;

	game->m.pos_x += M_HALF_PLAYER;
	game->m.pos_y += M_HALF_PLAYER;
	game->m.player_angle = game->m.a_rad;
	game->m.a_rad += M_RAYS * M_05_DEG_RAD;
	check_angle(game->m.a_rad, &game->m.a_deg);
	r.rays = -1;
	while (++r.rays < M_2RAYS)
	{
		r.dist_v = 0;
		r.dist_h = 0;
		r.atan = -1 / tan(-game->m.a_rad);
		r.ntan = -tan(-game->m.a_rad);
		ray_horizontal_check(&game->m, &r);
		ray_vertical_check(&game->m, &r);
		compare_dist(&r);
		draw_3d(game, &r);
		// draw_ray(&game->map, &game->m, &r, RED);						// à enlever plus tard
		game->m.a_rad -=  M_05_DEG_RAD;
		check_angle(game->m.a_rad, &game->m.a_deg);
	}
	game->m.pos_x -= M_HALF_PLAYER;
	game->m.pos_y -= M_HALF_PLAYER;
	game->m.a_rad += M_RAYS * M_05_DEG_RAD;
	game->m.a_deg = rad_to_deg(game->m.a_rad);
}
