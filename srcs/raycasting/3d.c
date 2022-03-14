#include "../../includes/cub3d.h"
#include "../../includes/map.h"

void	draw_lines(t_image *image, int x1, int y1, int x2, int y2, int color)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = x1;
	pixel_y = y1;
	while (pixels)
	{
		my_mlx_pixel_put(image, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

void	draw_3d(t_game *game, t_rays *r)
{
	int			line_h;
	int			lines;
	int			ray_w;
	float		offset;
	static int	start_x = 0;

	r->dist *= fix_fisheye(game->m.player_angle - game->m.a_rad);
	line_h = game->world_h * game->m.m_size / r->dist;
	if (line_h > game->world_h)
		line_h = game->world_h;
	offset = (game->world_h / 2) - (line_h / 2);
	lines = -1;
	ray_w = game->width / M_2RAYS;
	while (++lines < ray_w)
	{
		draw_lines(&game->world, start_x + lines, 0, start_x + lines, game->world_h, M_WALL_COLOR);
		draw_lines(&game->world, start_x + lines, offset, start_x + lines, line_h + offset, PURPLE);
	}
	start_x += ray_w;
	if (r->rays == M_2RAYS - 1)
		start_x = 0;
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
