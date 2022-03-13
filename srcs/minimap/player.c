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

int	miniplayer_move(t_game *game, t_image *map, char move, t_map *m)
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
	if (move_north(m) && move_south(m) && move_west(m) && move_east(m))
	{
		// remove_prev_pos(map, m);	// à réutiliser lorsqu'on affiche plus le FOV
		remove_prev_fov(map, m);
		new_player_pos(map, m, M_PLAYER_COLOR);
		new_player_fov(map, m);
		cast_rays(game, map, m);
		return (0);
	}
	m->pos_x = m->prev_x;
	m->pos_y = m->prev_y;
	return (-1);
}

int	miniplayer_move2(t_game *game, t_image *map, char move, t_map *m)			// for 'A' + 'S' keys
{
	(void) game;
	(void) map;
	(void) move;
	(void) m;
	return (0);
}

int	miniplayer_rotation(t_game *game, t_image *map, char dir, t_map *m)
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
	new_player_fov(map, m);
	cast_rays(game, map, m);
	return (0);
}
