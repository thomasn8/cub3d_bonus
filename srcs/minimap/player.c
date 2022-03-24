#include "../../includes/cub3d.h"
#include "../../includes/map.h"

void	remove_prev_fov(t_image *map, t_map *m)
{
	int	width;
	int	height;
	int	x;
	int	y;

	height = -2;
	while (++height < m->m_size * 2 + 2)
	{
		width = -2;
		while (++width < m->m_size * 2 + 2)
		{
			x = m->prev_x + width - m->m_size + M_HALF_PLAYER;
			y = m->prev_y + height - m->m_size + M_HALF_PLAYER;
			my_mlx_pixel_put(map, x, y, m->clean_map[y][x]);
		}
	}
}

/*
redessine entièrement la minimap
à utiliser lorsqu'on a besoin de projeter les rayons dans la minimap
la fonction du dessus est + rapide car redessine le minium nécessaire
*/
// void	remove_prev_fov(t_image *map, t_map *m)
// {
// 	int	width;
// 	int	height;

// 	height = -1;
// 	while (++height < m->h)
// 	{
// 		width = -1;
// 		while (++width < m->w)
// 			my_mlx_pixel_put(map, width, height, m->clean_map[height][width]);
// 	}
// }

void	new_fov(t_image *map, t_map *m)
{
	float	pixel_x;
	float	pixel_y;
	int		pixels;

	pixel_x = m->pos_x;
	pixel_y = m->pos_y;
	pixels = m->m_size;
	while (pixels)
	{
		my_mlx_pixel_put(map, pixel_x + M_HALF_PLAYER, pixel_y + M_HALF_PLAYER, M_FOV_COLOR);
		pixel_x += m->delta_x;
		pixel_y += m->delta_y;
		pixels--;
	}
}

void	new_pos(t_image *map, t_map *m, int color)
{
	int	width;
	int	height;

	height = -1;
	while (++height < M_PLAYER_SIZE)
	{
		width = -1;
		while (++width < M_PLAYER_SIZE)
			my_mlx_pixel_put(map, (int)m->pos_x + width, (int)m->pos_y + height, color);
	}
}

void	collision_check(t_map *m, t_grid *g, char k)
{
	g->of = 4;
	if (k == 'w')
		g->of = 2;
	g->xo = 0;
	if (m->delta_x < 0)
		g->xo = -g->of;
	else
		g->xo = g->of;
	g->yo = 0;
	if (m->delta_y < 0)
		g->yo = -g->of;
	else
		g->yo = g->of;
	g->vo = -1;
	g->ho = -1;
	if (m->a_deg > 180)
		g->vo += M_PS;
	if (m->a_deg < 90 || m->a_deg > 270)
		g->ho += M_PS;
	g->mx = (m->pos_x + g->ho) / m->m_size;
	g->mx_add_xo = (m->pos_x + g->ho + g->xo) / m->m_size;
	g->mx_sub_xo = (m->pos_x + g->ho - g->xo) / m->m_size;
	g->my = (m->pos_y + g->vo) / m->m_size;
	g->my_add_yo = (m->pos_y + g->vo + g->yo) / m->m_size;
	g->my_sub_yo = (m->pos_y + g->vo - g->yo) / m->m_size;
}

void	draw_all(t_game *game, char t)
{
	if (t == '2')
		remove_prev_fov(&game->map, &game->m);
	new_pos(&game->map, &game->m, M_PLAYER_COLOR);
	raycasting(game);
	new_fov(&game->map, &game->m);
}
