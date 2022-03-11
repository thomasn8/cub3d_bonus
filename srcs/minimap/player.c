#include "../../includes/cub3d.h"
#include "../../includes/map.h"

float deg_to_rad(int angle)
{
	return (angle * PI / 180.0);
}

int rad_to_deg(float angle)
{
	return (angle / PI * 180);
}

int	miniplayer_move(t_image *map, char move, t_map *m)
{
	m->prev_x = m->pos_x;
	m->prev_y = m->pos_y;
	if (move == 'w' && m->prev_y - M_DISTANCE >= 0)
		m->pos_y -= M_DISTANCE;
	else if (move == 's' && m->prev_y + M_DISTANCE * 2 <= m->h)
		m->pos_y += M_DISTANCE;
	else if (move == 'a' && m->prev_x - M_DISTANCE >= 0)
		m->pos_x -= M_DISTANCE;
	else if (move == 'd' && m->prev_x + M_DISTANCE * 2 <= m->w)
		m->pos_x += M_DISTANCE;
	else
		return (-1);
	if ((move == 's' && move_s(m)) || (move == 'd' && move_d(m)) ||
		(move == 'w' && move_w(m)) || (move == 'a' && move_a(m)) )
	{
		remove_prev_pos(map, m);
		remove_prev_fov(map, m);
		new_player_pos(map, m, M_PLAYER_COLOR);
		new_player_fov(map, m);
		cast_rays(map, m);
		return (0);
	}
	m->pos_x = m->prev_x;
	m->pos_y = m->prev_y;
	return (-1);
}

int	miniplayer_rotation(t_image *map, char dir, t_map *m)
{
	m->prev_delta_x = m->delta_x;
	m->prev_delta_y = m->delta_y;
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
	new_player_fov(map, m);
	cast_rays(map, m);
	return (-1);
}
