#include "../../includes/cub3d.h"
#include "../../includes/map.h"

void	cast_single_ray(t_game *game)
{
	game->m.player_angle = game->m.a_rad;
	game->r.dist_v = 0;
	game->r.dist_h = 0;
	game->r.atan = -1 / tan(-game->m.a_rad);
	game->r.ntan = -tan(-game->m.a_rad);
	ray_horizontal_check(&game->m, &game->r);
	ray_vertical_check(&game->m, &game->r);
	game->m.cross = compare_dist(&game->r);
	// printf("cross = %c\n", game->m.cross);
}

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

int	move_check(t_game *game, char move)
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;
	(void)	move;

	x1 = (game->m.pos_x - 1) / game->m.m_size;
	y1 = (game->m.pos_y - 1) / game->m.m_size;
	x2 = (game->m.pos_x + M_PLAYER_SIZE - 1) / game->m.m_size;
	y2 = (game->m.pos_y + M_PLAYER_SIZE - 1) / game->m.m_size;
	
	if (game->m.map[(int)y1][(int)x1] != '1' &&
		game->m.map[(int)y2][(int)x2] != '1' &&
		game->m.map[(int)y1][(int)x2] != '1' &&
		game->m.map[(int)y2][(int)x1] != '1')
		return (1);

	if (game->m.cross == 'v') 						// et contre un mur vertical
		game->m.pos_x = game->m.prev_x;
	if (game->m.cross == 'h') 						// et contre un mur horizontal
		game->m.pos_y = game->m.prev_y;
	
	return (1);
}

int	move(t_game *game, char dir)
{
	game->m.prev_x = game->m.pos_x;
	game->m.prev_y = game->m.pos_y;

	cast_single_ray(game);
	if (dir == 'w')
	{
		game->m.pos_x += game->m.delta_x * game->m.ws_fps;
		game->m.pos_y += game->m.delta_y * game->m.ws_fps;
	}
	else if (dir == 's')
	{
		game->m.pos_x -= game->m.delta_x * game->m.ws_fps;
		game->m.pos_y -= game->m.delta_y * game->m.ws_fps;
	}
	else if (dir == 'a')
		a_move(&game->m);
	else if (dir == 'd')
		d_move(&game->m);
	move_check(game, 'a');
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
