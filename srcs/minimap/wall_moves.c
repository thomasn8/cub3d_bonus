#include "../../includes/cub3d.h"
#include "../../includes/map.h"

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
