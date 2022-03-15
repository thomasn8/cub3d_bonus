#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	collision_check(t_map *m, t_grid *g)
{
	m->prev_x = m->pos_x;
	m->prev_y = m->pos_y;
	g->xo = 0;
	if (m->delta_x < 0)
		g->xo = -4;
	else
		g->xo = 4;
	g->yo = 0;
	if (m->delta_y < 0)
		g->yo = -4;
	else
		g->yo = 4;
	g->vo = -1;
	g->ho = -1;
	if (m->a_deg > 180)
		g->vo += M_PS;
	if (m->a_deg < 90 || m->a_deg > 270)
		g->ho += M_PS;
	g->mx		 = (m->pos_x + g->ho) / m->m_size;
	g->mx_add_xo = (m->pos_x + g->ho + g->xo) / m->m_size;
	g->mx_sub_xo = (m->pos_x + g->ho - g->xo) / m->m_size;
	g->my		 = (m->pos_y + g->vo) / m->m_size;
	g->my_add_yo = (m->pos_y + g->vo + g->yo) / m->m_size;
	g->my_sub_yo = (m->pos_y + g->vo - g->yo) / m->m_size;
}

static void	a_move(t_game *game, t_map *m)
{
	t_grid g;

	m->a_rad += M_RAD_90;
	if (m->a_rad > PI2)
		m->a_rad -= PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	collision_check(&game->m, &g);
	if (game->m.map[g.my][g.mx_add_xo] != '1')
		m->pos_x += m->delta_x * m->ad_fps;
	if (game->m.map[g.my_add_yo][g.mx] != '1')
		m->pos_y += m->delta_y * m->ad_fps;
	m->a_rad -= M_RAD_90;
	if (m->a_rad < 0)
		m->a_rad += PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
}

static void	d_move(t_game *game, t_map *m)
{
	t_grid g;

	m->a_rad -= M_RAD_90;
	if (m->a_rad < 0)
		m->a_rad += PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
	collision_check(&game->m, &g);
	if (game->m.map[g.my][g.mx_add_xo] != '1')
		m->pos_x += m->delta_x * m->ad_fps;
	if (game->m.map[g.my_add_yo][g.mx] != '1')
		m->pos_y += m->delta_y * m->ad_fps;
	m->a_rad += M_RAD_90;
	if (m->a_rad > PI2)
		m->a_rad -= PI2;
	m->delta_x = cos(-m->a_rad);
	m->delta_y = sin(-m->a_rad);
}

void	move(t_game *game, char dir)
{
	collision_check(&game->m, &game->g);
	if (dir == 'w')
	{
		if (game->m.map[game->g.my][game->g.mx_add_xo] != '1')
			game->m.pos_x += game->m.delta_x * game->m.ws_fps;
		if (game->m.map[game->g.my_add_yo][game->g.mx] != '1')
			game->m.pos_y += game->m.delta_y * game->m.ws_fps;
	}
	else if (dir == 's')
	{
		if (game->m.map[game->g.my][game->g.mx_sub_xo] != '1')
			game->m.pos_x -= game->m.delta_x * game->m.ws_fps;
		if (game->m.map[game->g.my_sub_yo][game->g.mx] != '1')
			game->m.pos_y -= game->m.delta_y * game->m.ws_fps;
	}
	else if (dir == 'a')
		a_move(game, &game->m);
	else if (dir == 'd')
		d_move(game, &game->m);
	remove_prev_fov(&game->map, &game->m);
	new_pos(&game->map, &game->m, M_PLAYER_COLOR);
	raycasting(game);
	new_fov(&game->map, &game->m);
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
	remove_prev_fov(&game->map, &game->m);
	new_pos(&game->map, &game->m, M_PLAYER_COLOR);
	raycasting(game);
	new_fov(&game->map, &game->m);
}
