#include "../../includes/cub3d.h"
#include "../../includes/map.h"

int	move_ok(t_map *m)
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;

	x1 = (m->pos_x - 1) / m->m_size;
	y1 = (m->pos_y - 1) / m->m_size;
	x2 = (m->pos_x + M_PLAYER_SIZE - 1) / m->m_size;
	y2 = (m->pos_y + M_PLAYER_SIZE - 1) / m->m_size;
	if (m->map[(int)y1][(int)x1] != '1' &&
		m->map[(int)y2][(int)x2] != '1' &&
		m->map[(int)y1][(int)x2] != '1' &&
		m->map[(int)y2][(int)x1] != '1')
		return (1);
	return (0);
}

// int	wall_a_move(t_game *game, t_image *map, t_map *m)
// {
// 	float	a_prev;

// 	m->prev_x = m->pos_x;
// 	m->prev_y = m->pos_y;
// 	a_prev = m->a_rad;
// 	m->a_rad = M_RAD_180;
// 	m->delta_x = cos(-m->a_rad);
// 	m->delta_y = sin(-m->a_rad);
// 	m->pos_x += m->delta_x;
// 	m->pos_y += m->delta_y;
// 	m->a_rad = a_prev;
// 	m->delta_x = cos(-m->a_rad);
// 	m->delta_y = sin(-m->a_rad);
// 	if (move_ok(m))
// 	{
// 		// remove_prev_pos(map, m);	// à réutiliser lorsqu'on n'affiche plus le FOV
// 		remove_prev_fov(map, m);
// 		new_pos(map, m, M_PLAYER_COLOR);
// 		raycasting(game, map, m);
// 		new_fov(map, m);
// 		return (0);
// 	}
// 	m->pos_x = m->prev_x;
// 	m->pos_y = m->prev_y;
// 	return (-1);
// }

// int	wall_d_move(t_game *game, t_image *map, t_map *m)
// {
// 	float	a_prev;

// 	m->prev_x = m->pos_x;
// 	m->prev_y = m->pos_y;
// 	a_prev = m->a_rad;
// 	m->a_rad = M_RAD_0;
// 	m->delta_x = cos(-m->a_rad);
// 	m->delta_y = sin(-m->a_rad);
// 	m->pos_x += m->delta_x;
// 	m->pos_y += m->delta_y;
// 	m->a_rad = a_prev;
// 	m->delta_x = cos(-m->a_rad);
// 	m->delta_y = sin(-m->a_rad);
// 	if (move_ok(m))
// 	{
// 		// remove_prev_pos(map, m);	// à réutiliser lorsqu'on n'affiche plus le FOV
// 		remove_prev_fov(map, m);
// 		new_pos(map, m, M_PLAYER_COLOR);
// 		raycasting(game, map, m);
// 		new_fov(map, m);
// 		return (0);
// 	}
// 	m->pos_x = m->prev_x;
// 	m->pos_y = m->prev_y;
// 	return (-1);
// }
