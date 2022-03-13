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

void	a_move(t_map *m)
{
	m->a_rad += M_RAD_90;
	if (m->a_rad > PI2)
		m->a_rad -= PI2;
	m->a_deg = rad_to_deg(m->a_rad);
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	m->pos_x += m->delta_x;
	m->pos_y += m->delta_y;
	m->a_rad -= M_RAD_90;
	if (m->a_rad < 0)
		m->a_rad += PI2;
	m->a_deg = rad_to_deg(m->a_rad);
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
}

void	d_move(t_map *m)
{
	m->a_rad -= M_RAD_90;
	if (m->a_rad < 0)
		m->a_rad += PI2;
	m->a_deg = rad_to_deg(m->a_rad);
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	m->pos_x += m->delta_x;
	m->pos_y += m->delta_y;
	m->a_rad += M_RAD_90;
	if (m->a_rad > PI2)
		m->a_rad -= PI2;
	m->a_deg = rad_to_deg(m->a_rad);
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
}

void	wsad(t_map *m, char move)
{
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
	else if (move == 'a')
		a_move(m);
	else if (move == 'd')
		d_move(m);
}

int	move(t_game *game, t_image *map, char move, t_map *m)
{
	m->prev_x = m->pos_x;
	m->prev_y = m->pos_y;
	wsad(m, move);
	if (move_check(m))
	{
		// remove_prev_pos(map, m);	// à réutiliser lorsqu'on n'affiche plus le FOV
		remove_prev_fov(map, m);
		new_pos(map, m, M_PLAYER_COLOR);
		raycasting(game, map, m);
		new_fov(map, m);
		return (0);
	}
	m->pos_x = m->prev_x;
	m->pos_y = m->prev_y;
	return (-1);
}

int	rotation(t_game *game, t_image *map, char dir, t_map *m)
{
	if (dir == 'l')
	{
		m->a_rad -= 5 * M_1_DEG_RAD;
		if (m->a_rad < 0)
			m->a_rad += PI2;
	}
	else if (dir == 'r')
	{
		m->a_rad += 5 * M_1_DEG_RAD;
		if (m->a_rad > PI2)
			m->a_rad -= PI2;
	}
	m->a_deg = rad_to_deg(m->a_rad);
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	remove_prev_fov(map, m);
	new_pos(map, m, M_PLAYER_COLOR);
	raycasting(game, map, m);
	new_fov(map, m);
	return (0);
}
