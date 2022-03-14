#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	a_move(t_map *m)
{
	m->a_rad += M_RAD_90;
	if (m->a_rad > PI2)
		m->a_rad -= PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	m->pos_x += m->delta_x;
	m->pos_y += m->delta_y;
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
	m->pos_x += m->delta_x;
	m->pos_y += m->delta_y;
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
		m->pos_x += m->delta_x;
		m->pos_y += m->delta_y;
	}
	else if (dir == 's')
	{
		m->pos_x -= m->delta_x;
		m->pos_y -= m->delta_y;
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
	// else
	// {
	// 	// if (game->m.a_deg > 0 && game->m.a_deg < 180) 							// appuyé contre mur en haut
	// 	// {
	// 	// 	if (game->m.a_deg < 90)
	// 	// 		return (wall_d_move(game, &game->map, &game->m));
	// 	// 	else if (game->m.a_deg > 90)
	// 	// 		return (wall_a_move(game, &game->map, &game->m));
	// 	// }
	// 	// else if (game->m.a_deg > 180 && game->m.a_deg < 360) 						// appuyé contre mur en bas
	// 	// else if (game->m.a_deg > 90 && game->m.a_deg < 270)						// appuyé contre mur à gauche
	// 	// else if (game->m.a_deg != 0 && (game->m.a_deg < 90 || game->m.a_deg > 270)) 	// appuyé contre mur à droite
	// }
	game->m.pos_x = game->m.prev_x;
	game->m.pos_y = game->m.prev_y;
	return (-1);
}

int	rotation(t_game *game, char dir)
{
	if (dir == 'l')
	{
		game->m.a_rad -= M_ROT_SPEED * M_1_DEG_RAD;
		if (game->m.a_rad < 0)
			game->m.a_rad += PI2;
	}
	else if (dir == 'r')
	{
		game->m.a_rad += M_ROT_SPEED * M_1_DEG_RAD;
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
