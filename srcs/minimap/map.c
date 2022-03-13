#include "../../includes/cub3d.h"
#include "../../includes/map.h"

// A RECEVOIR DU PARSING
# define S_X 31
# define S_Y 1
# define S_ANGLE 180
//////////////////////////////////////

static unsigned int	**copy_map(t_image *map, int width, int heigth)
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

static void	color_map(t_image *map, t_map *m)
{
	while (++m->y < m->rows)
	{
		m->x = -1;
		while (++m->x < m->cols)
		{
			if (m->map[m->y][m->x] == '1')
				m->color = M_WALL_COLOR;
			else
				m->color = M_SPACE_COLOR;
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

int	block_size(int cols, int rows)
{
	int max_w;
	int max_h;
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

void	minimap_init(t_game *game, t_parse *parse)
{
	// A COMPLETER GRACE AU PARSING
	// map
	game->m.map = parse->map;
	// dimensions
	game->m.cols = parse->m_width;
	game->m.rows =  parse->m_height;
	game->m.m_size = block_size(game->m.cols, game->m.rows);
	game->m.w = parse->m_width * game->m.m_size;
	game->m.h = parse->m_height * game->m.m_size;
	game->m.offset = game->world_h + MARGIN + ((MENU_HEIGTH - (2 * MARGIN)) - game->m.h) / 2;
	game->map.image = mlx_new_image(game->mlx, game->m.w, game->m.h);
	game->map.addr = mlx_get_data_addr(game->map.image, &game->map.bits_per_pixel,
			&game->map.line_length, &game->map.endian);
	// player position
	// printf("Player position: %d,%d\n", parse->start_x, parse->start_y);
	game->m.pos_x = (S_X * game->m.m_size) + (0.5 * game->m.m_size) - (0.5 * M_PLAYER_SIZE);
	game->m.pos_y = (S_Y * game->m.m_size) + (0.5 * game->m.m_size) - (0.5 * M_PLAYER_SIZE);
	game->m.prev_x = game->m.pos_x;
	game->m.prev_y = game->m.pos_y;
	// player orientation
	// printf("Player orientation: %c\n", parse->start_player);
	game->m.a_rad = deg_to_rad(S_ANGLE);
	game->m.a_deg = S_ANGLE;
	game->m.delta_x = cos(game->m.a_rad * 5);
	game->m.delta_y = sin(game->m.a_rad * 5);
	///////////////////////////////

	game->m.y = -1;
	color_map(&game->map, &game->m);
	game->m.clean_map = copy_map(&game->map, game->m.w, game->m.h);
	new_pos(&game->map, &game->m, M_PLAYER_COLOR);
	raycasting(game, &game->map, &game->m);
	new_fov(&game->map, &game->m);
}
