#include "../../includes/cub3d.h"
#include "../../includes/map.h"

void	draw_lines(t_image *image, int x1, int y1, int x2, int y2, int color)
{
	double	d_x;
	double	d_y;
	int		pix;
	double	p_x;
	double	p_y;

	d_x = x2 - x1;
	d_y = y2 - y1;
	pix = sqrt((d_x * d_x) + (d_y * d_y));
	d_x /= pix;
	d_y /= pix;
	p_x = x1;
	p_y = y1;
	while (pix)
	{
		my_mlx_pixel_put(image, p_x, p_y, color);
		p_x += d_x;
		p_y += d_y;
		--pix;
	}
}

// l = line | lpr = lines per ray | bot = wall bottom | top = wall top
void	draw_3d(t_game *game, t_rays *r)
{
	int			l;
	int			top;
	float		bot;
	int			lpr;
	static int	x = 0;

	r->dist *= fix_fisheye(game->m.player_angle - game->m.a_rad);
	top = game->world_h * game->m.m_size / r->dist;
	if (top > game->world_h)
		top = game->world_h;
	bot = (game->world_h / 2) - (top / 2);
	lpr = game->width / M_2RAYS;
	l = -1;
	while (++l < lpr)
	{
		draw_lines(&game->world, x + l, 0, x + l, bot - 1, GREEN);							// c_s
		draw_lines(&game->world, x + l, bot, x + l, top + bot - 1, PURPLE);					// wall
		draw_lines(&game->world, x + l, top + bot, x + l, game->world_h, M_WALL_COLOR);		// c_f
	}
	x += lpr;
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
		draw_ray(&game->map, &game->m, &r, RED);						// à enlever plus tard
		game->m.a_rad -=  M_05_DEG_RAD;
		check_angle(game->m.a_rad, &game->m.a_deg);
	}
	game->m.pos_x -= M_HALF_PLAYER;
	game->m.pos_y -= M_HALF_PLAYER;
	game->m.a_rad += M_RAYS * M_05_DEG_RAD;
	game->m.a_deg = rad_to_deg(game->m.a_rad);
}
