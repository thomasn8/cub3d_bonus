#include "../../includes/cub3d.h"
#include "../../includes/map.h"

int	move_north(t_map *m)
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;

	x1 = (m->pos_x - 1) / m->m_size;
	y1 = (m->pos_y - 1) / m->m_size;
	x2 = (m->pos_x + M_PLAYER_SIZE - 1) / m->m_size;
	y2 = (m->pos_y - 1) / m->m_size;
	if (m->map[(int)y1][(int)x1] != '1' &&
		m->map[(int)y2][(int)x2] != '1')
		return (1);
	return (0);
}

int	move_south(t_map *m)
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;

	x1 = (m->pos_x - 1) / m->m_size;
	y1 = (m->pos_y + M_PLAYER_SIZE - 1) / m->m_size;
	x2 = (m->pos_x + M_PLAYER_SIZE - 1) / m->m_size;
	y2 = (m->pos_y + M_PLAYER_SIZE - 1) / m->m_size;
	if (m->map[(int)y1][(int)x1] != '1' &&
		m->map[(int)y2][(int)x2] != '1')
		return (1);
	return (0);
}

int	move_east(t_map *m)
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;

	x1 = (m->pos_x + M_PLAYER_SIZE - 1) / m->m_size;
	y1 = (m->pos_y - 1) / m->m_size;
	x2 = (m->pos_x + M_PLAYER_SIZE - 1) / m->m_size;
	y2 = (m->pos_y + M_PLAYER_SIZE - 1) / m->m_size;
	if (m->map[(int)y1][(int)x1] != '1' &&
		m->map[(int)y2][(int)x2] != '1')
		return (1);
	return (0);
}

int	move_west(t_map *m)
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;

	x1 = (m->pos_x - 1) / m->m_size;
	y1 = (m->pos_y - 1) / m->m_size;
	x2 = (m->pos_x - 1) / m->m_size;
	y2 = (m->pos_y + M_PLAYER_SIZE - 1) / m->m_size;
	if (m->map[(int)y1][(int)x1] != '1' &&
		m->map[(int)y2][(int)x2] != '1')
		return (1);
	return (0);
}
