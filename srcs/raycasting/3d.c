#include "../../includes/cub3d.h"
#include "../../includes/map.h"

// int fix_fisheye(int a)
// { 
// 	if (a > 359)
// 		a -= 360;
// 	if (a < 0)
// 		a += 360;
// 	return (a);
// }

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


void	draw_3d(t_game *game, t_map *m, t_rays *r)
{
	int			line_h;
	int			lines;
	static int	start_x = 0;
	int			ray_w;
	float		offset;

	// int angle;
	// angle = fix_fisheye(rad_to_deg(m->a_rad - r->ray_angle));
	// r->dist *= cos(deg_to_rad(angle));

	line_h = game->world_h * m->m_size / r->dist;
	if (line_h > game->world_h)
		line_h = game->world_h;
	offset = (game->world_h / 2) - (line_h / 2);
	lines = -1;
	ray_w = game->width / M_RAYS;
	while (++lines < ray_w)
	{
		draw_lines(&game->world, start_x + lines, 0, start_x + lines, game->world_h, M_WALL_COLOR);
		draw_lines(&game->world, start_x + lines, offset, start_x + lines, line_h + offset, PURPLE);
	}
	if (r->rays > 1)
		start_x += ray_w;
	else
		start_x = 0;
}

void	cast_rays(t_game *game, t_image *map, t_map *m)
{
	t_rays	r;
	(void) map;

	m->pos_x += M_HALF_PLAYER;
	m->pos_y += M_HALF_PLAYER;
	m->a_rad += M_HALF_RAYS * M_1_DEG_RAD;
	check_angle(m->a_rad, &m->a_deg);
	r.rays = -1;
	while (++r.rays < M_RAYS)
	{
		init_casting(&r, m->a_rad);
		r.i = -1;
		horizontal_wall_intersection(m, &r);
		r.i = -1;
		vertical_wall_intersection(m, &r);
		compare_dist(&r);
		r.ray_angle = m->a_rad;
		draw_3d(game, m, &r);
		// draw_ray(map, m, &r, RED);						// à enlever plus tard
		m->a_rad -=  M_1_DEG_RAD;
		check_angle(m->a_rad, &m->a_deg);
	}
	m->pos_x -= M_HALF_PLAYER;
	m->pos_y -= M_HALF_PLAYER;
	m->a_rad += M_HALF_RAYS * M_1_DEG_RAD;
	m->a_deg = rad_to_deg(m->a_rad);
}
