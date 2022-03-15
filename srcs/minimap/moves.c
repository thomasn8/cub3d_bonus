#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	a_move(t_map *m)
{
	m->a_rad += M_RAD_90;
	if (m->a_rad > PI2)
		m->a_rad -= PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	m->pos_x += m->delta_x * m->ad_fps;
	m->pos_y += m->delta_y * m->ad_fps;
	m->a_rad -= M_RAD_90;
	if (m->a_rad < 0)
		m->a_rad += PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
}

static void	d_move(t_map *m)
{
	m->a_rad -= M_RAD_90;
	if (m->a_rad < 0)
		m->a_rad += PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	m->pos_x += m->delta_x * m->ad_fps;
	m->pos_y += m->delta_y * m->ad_fps;
	m->a_rad += M_RAD_90;
	if (m->a_rad > PI2)
		m->a_rad -= PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
}

static void	wsad(t_map *m, char dir)
{
	if (dir == 'w')
	{
		m->pos_x += m->delta_x * m->ws_fps;
		m->pos_y += m->delta_y * m->ws_fps;
	}
	else if (dir == 's')
	{
		m->pos_x -= m->delta_x * m->ws_fps;
		m->pos_y -= m->delta_y * m->ws_fps;
	}
	else if (dir == 'a')
		a_move(m);
	else if (dir == 'd')
		d_move(m);
}

int	move(t_game *game, char dir)
{
	game->m.prev_x = game->m.pos_x;
	game->m.prev_y = game->m.pos_y;
	wsad(&game->m, dir);
	if (move_ok(&game->m))
	{
		remove_prev_fov(&game->map, &game->m);
		new_pos(&game->map, &game->m, M_PLAYER_COLOR);
		raycasting(game);
		new_fov(&game->map, &game->m);
		return (0);
	}
	game->m.pos_x = game->m.prev_x;
	game->m.pos_y = game->m.prev_y;
	return (-1);
}

int	rotation(t_game *game, char dir)
{
	if (dir == 'l')
	{
		game->m.a_rad -= M_1_DEG_RAD * game->m.rot_fps;
		if (game->m.a_rad < 0)
			game->m.a_rad += PI2;
	}
	else if (dir == 'r')
	{
		game->m.a_rad += M_1_DEG_RAD * game->m.rot_fps;
		if (game->m.a_rad > PI2)
			game->m.a_rad -= PI2;
	}
	game->m.a_deg = rad_to_deg(game->m.a_rad);
	game->m.delta_x = cos(-game->m.a_rad);
	game->m.delta_y = sin(-game->m.a_rad);
	remove_prev_fov(&game->map, &game->m);
	new_pos(&game->map, &game->m, M_PLAYER_COLOR);
	raycasting(game);
	new_fov(&game->map, &game->m);
	return (0);
}
