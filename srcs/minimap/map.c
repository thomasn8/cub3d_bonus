#include "../../includes/cub3d.h"
#include "../../includes/map.h"

// A RECEVOIR DU PARSING
# define S_X 9
# define S_Y 1
# define S_ANGLE 0
// A CALCULER A PARTIR DU PARSING
# define START_X  (S_X * M_SIZE) + (0.5 * M_SIZE) - (0.5 * M_PLAYER_SIZE)
# define START_Y  (S_Y * M_SIZE) + (0.5 * M_SIZE) - (0.5 * M_PLAYER_SIZE)
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
			m->yo = (m->y + 1) * M_SIZE;
			while (m->yo-- > m->y * M_SIZE)
			{
				m->xo = (m->x + 1) * M_SIZE;
				while (m->xo-- > m->x * M_SIZE)
				{
					if (m->xo % M_SIZE == 0 || m->yo % M_SIZE == 0
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

void	minimap_init(t_game *game, t_parse *parse)
{
	game->map.image = mlx_new_image(game->mlx, parse->m_width * M_SIZE, parse->m_height * M_SIZE);
	game->map.addr = mlx_get_data_addr(game->map.image, &game->map.bits_per_pixel,
			&game->map.line_length, &game->map.endian);
	
	// A COMPLETER GRACE AU PARSING
	// map
	game->m.map = parse->map;
	// dimensions
	game->m.w = parse->m_width * M_SIZE;
	game->m.h = parse->m_height * M_SIZE;
	game->m.cols = parse->m_width;
	game->m.rows =  parse->m_height;
	printf("Dimensions:\n%d rows / %d cols (%d * %d pixels)\n",game->m.rows, game->m.cols, game->m.w, game->m.h);
	// player position
	// printf("Player position: %d,%d\n", parse->start_x, parse->start_y);
	game->m.prev_x = START_X;
	game->m.prev_y = START_Y;
	game->m.pos_x = START_X;
	game->m.pos_y = START_Y;
	// player orientation
	// printf("Player orientation: %c\n", parse->start_player);
	game->m.a_rad = M_RAD_0;
	game->m.a_deg = M_EAST;
	game->m.delta_x = cos(game->m.a_rad * 5);
	game->m.delta_y = sin(game->m.a_rad * 5);
	///////////////////////////////

	game->m.y = -1;
	color_map(&game->map, &game->m);
	game->m.clean_map = copy_map(&game->map, game->m.w, game->m.h);
	new_player_pos(&game->map, &game->m, M_PLAYER_COLOR);
	new_player_fov(&game->map, &game->m);
	cast_rays(game, &game->map, &game->m);
}
