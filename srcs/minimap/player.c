#include "../../includes/cub3d.h"
#include "../../includes/map.h"

// void	remove_prev_fov(t_image *map, t_map *m)
// {
// 	int	width;
// 	int	height;
// 	int x;
// 	int y;

// 	height = -2;
// 	while (++height < m->m_size * 2 + 1)
// 	{
// 		width = -2;
// 		while (++width < m->m_size * 2 + 1)
// 		{
// 			x = m->prev_x + width - m->m_size + M_HALF_PLAYER;
// 			y = m->prev_y + height - m->m_size + M_HALF_PLAYER;
// 			my_mlx_pixel_put(map, x, y, m->clean_map[y][x]);
// 		}
// 	}
// }

/* 
redessine entièrement la minimap
à utiliser lorsqu'on a besoin de projeter les rayons dans la minimap
la fonction du dessus est + rapide car redessine le minium nécessaire 
*/
void	remove_prev_fov(t_image *map, t_map *m)
{
	int	width;
	int	height;

	height = -1;
	while (++height < m->h)
	{
		width = -1;
		while (++width < m->w)
			my_mlx_pixel_put(map, width, height, m->clean_map[height][width]);
	}
}

void	remove_prev_pos(t_image *map, t_map *m)
{
	int	width;
	int	height;
	int x;
	int y;

	height = -1;
	while (++height < M_PLAYER_SIZE)
	{
		width = -1;
		while (++width < M_PLAYER_SIZE)
		{
			x = m->prev_x + width;
			y = m->prev_y + height;
			my_mlx_pixel_put(map, x, y,  m->clean_map[y][x]);
		}
	}
}

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
