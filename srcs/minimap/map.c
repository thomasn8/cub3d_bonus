/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:15:14 by tnanchen          #+#    #+#             */
/*   Updated: 2022/03/24 08:16:35 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/map.h"

unsigned int	**copy_map(t_image *map, int width, int heigth)
{
	int				x;
	int				y;
	unsigned int	**copy;

	copy = malloc((heigth + 1) * sizeof(unsigned int *));
	if (!copy)
		return (NULL);
	copy[heigth] = NULL;
	y = -1;
	while (++y < heigth)
	{
		copy[y] = malloc(width * sizeof(unsigned int));
		if (!copy[y])
			return (NULL);
		x = -1;
		while (++x < width)
			copy[y][x] = *(unsigned int *)(map->addr
					+ (y * map->line_length
						+ x * (map->bits_per_pixel / 8)));
	}
	return (copy);
}

static int	color(char c)
{
	if (c == '0')
		return (M_SPACE_COLOR);
	else if (c >= '1' && c <= W_TEX)
		return (M_WALL_COLOR);
	else if (c == '9')
		return (M_DOOR_COLOR);
	return (0);
}

void	color_map(t_image *map, t_map *m)
{
	m->y = -1;
	while (++m->y < m->rows)
	{
		m->x = -1;
		while (++m->x < m->cols)
		{
			m->color = color(m->map[m->y][m->x]);
			m->yo = (m->y + 1) * m->m_size;
			while (m->yo-- > m->y * m->m_size)
			{
				m->xo = (m->x + 1) * m->m_size;
				while (m->xo-- > m->x * m->m_size)
				{
					if (m->xo % m->m_size == 0 || m->yo % m->m_size == 0
						|| m->xo == m->w - 1
						|| m->yo == m->h - 1)
						my_mlx_pixel_put(map, m->xo, m->yo, M_GRID_COLOR);
					else
						my_mlx_pixel_put(map, m->xo, m->yo, m->color);
				}
			}
		}
	}
}

// détermine la taille d'un block en pixel dans la minimap
// et centre la minimap dans la barre du bas
static int	get_m_size(int cols, int rows)
{
	int	max_w;
	int	max_h;
	int	m_size1;
	int	m_size2;

	max_w = (WIDTH / 2) - (2 * MARGIN);
	max_h = MENU_HEIGTH - (2 * MARGIN);
	m_size1 = max_w / cols;
	m_size2 = max_h / rows;
	if (m_size1 > m_size2)
		return (m_size2);
	return (m_size1);
}

void	map_description(t_game *game, t_parse *parse)
{
	game->m.map = parse->map;
	game->m.cols = parse->m_width;
	game->m.rows = parse->m_height;
	game->m.m_size = get_m_size(game->m.cols, game->m.rows);
	game->m.w = parse->m_width * game->m.m_size;
	game->m.h = parse->m_height * game->m.m_size;
	game->m.h_offset = game->world_h + MARGIN
		+ ((MENU_HEIGTH - (2 * MARGIN)) - game->m.h) / 2;
	game->m.w_offset = (game->width - (2 * MARGIN) - game->m.w) / 2;
	game->map.image = mlx_new_image(game->mlx, game->m.w, game->m.h);
	game->map.addr = mlx_get_data_addr(game->map.image,
			&game->map.bits_per_pixel, &game->map.line_length,
			&game->map.endian);
	game->m.no = parse->no;
	game->m.so = parse->so;
	game->m.we = parse->we;
	game->m.ea = parse->ea;
	game->m.c_floor = parse->hex_f;
	game->m.c_ceil = parse->hex_s;
}
