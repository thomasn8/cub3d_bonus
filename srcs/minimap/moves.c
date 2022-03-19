#include "../../includes/cub3d.h"
#include "../../includes/map.h"

int	map_char(char c)
{
	if (c <= W_TEX && c >= '1')
		return (0);
	return (1);
}

static void	a_move(t_map *m)
{
	t_grid g;

	m->a_rad += M_RAD_90;
	if (m->a_rad > PI2)
		m->a_rad -= PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	collision_check(m, &g, 'a');
	if (map_char(m->map[g.my][g.mx_add_xo]))
		m->pos_x += m->delta_x * m->ad_fps;
	if (map_char(m->map[g.my_add_yo][g.mx]))
		m->pos_y += m->delta_y * m->ad_fps;
	m->a_rad -= M_RAD_90;
	if (m->a_rad < 0)
		m->a_rad += PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
}

static void	d_move(t_map *m)
{
	t_grid g;

	m->a_rad -= M_RAD_90;
	if (m->a_rad < 0)
		m->a_rad += PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	collision_check(m, &g, 'd');
	if (map_char(m->map[g.my][g.mx_add_xo]))
		m->pos_x += m->delta_x * m->ad_fps;
	if (map_char(m->map[g.my_add_yo][g.mx]))
		m->pos_y += m->delta_y * m->ad_fps;
	m->a_rad += M_RAD_90;
	if (m->a_rad > PI2)
		m->a_rad -= PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
}

void	move(t_game *game, char dir)
{
	game->m.prev_x = game->m.pos_x;
	game->m.prev_y = game->m.pos_y;
	if (dir == 'w')
	{
		collision_check(&game->m, &game->g, 'w');
		if (map_char(game->m.map[game->g.my][game->g.mx_add_xo]))
			game->m.pos_x += game->m.delta_x * game->m.ws_fps;
		if (map_char(game->m.map[game->g.my_add_yo][game->g.mx]))
			game->m.pos_y += game->m.delta_y * game->m.ws_fps;
	}
	else if (dir == 's')
	{
		collision_check(&game->m, &game->g, 's');
		if (map_char(game->m.map[game->g.my][game->g.mx_sub_xo]))
			game->m.pos_x -= game->m.delta_x * game->m.ws_fps;
		if (map_char(game->m.map[game->g.my_sub_yo][game->g.mx]))
			game->m.pos_y -= game->m.delta_y * game->m.ws_fps;
	}
	else if (dir == 'a')
		a_move(&game->m);
	else if (dir == 'd')
		d_move(&game->m);
	draw_all(game, '2');
}

void	rotation(t_game *game, char dir)
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
	draw_all(game, '2');
}
