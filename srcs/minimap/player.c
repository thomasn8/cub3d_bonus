#include "../../includes/cub3d.h"
#include "../../includes/map.h"

int	move_check(t_map *m)
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

int	player_move(t_game *game, t_image *map, char move, t_map *m)
{
	m->prev_x = m->pos_x;
	m->prev_y = m->pos_y;
	if (move == 'w')
	{
		m->pos_x += m->delta_x;
		m->pos_y += m->delta_y;
	}
	else if (move == 's')
	{
		m->pos_x -= m->delta_x;
		m->pos_y -= m->delta_y;
	}
	if (move_check(m))
	{
		// remove_prev_pos(map, m);	// à réutiliser lorsqu'on n'affiche plus le FOV
		remove_prev_fov(map, m);
		new_player_pos(map, m, M_PLAYER_COLOR);
		cast_rays(game, map, m);
		new_player_fov(map, m);
		return (0);
	}
	m->pos_x = m->prev_x;
	m->pos_y = m->prev_y;
	return (-1);
}

int	player_move2(t_game *game, t_image *map, char move, t_map *m)			// for 'A' + 'S' keys
{
	(void) game;
	(void) map;
	(void) move;
	(void) m;
	return (0);
}

int	player_rotation(t_game *game, t_image *map, char dir, t_map *m)
{
	if (dir == 'l')
	{
		m->a_rad -= 5 * M_1_DEG_RAD;
		if (m->a_rad < 0)
			m->a_rad += 2 * PI;
	}
	else if (dir == 'r')
	{
		m->a_rad += 5 * M_1_DEG_RAD;
		if (m->a_rad > 2 * PI)
			m->a_rad -= 2 * PI;
	}
	m->a_deg = rad_to_deg(m->a_rad);
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	remove_prev_fov(map, m);
	new_player_pos(map, m, M_PLAYER_COLOR);
	cast_rays(game, map, m);
	new_player_fov(map, m);
	return (0);
}
