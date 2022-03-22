#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	enemies_error(char *msg)
{
	write(2, msg, 29);
	exit(1);
}

void	tex_enemies_create(t_game *game)
{
	game->sheeps[0].tex_sheepl.image = mlx_xpm_file_to_image(
		game->mlx, "./enemies/sheepl", &game->sheeps[0].tex_sheepl.width, &game->sheeps[0].tex_sheepl.heigth);
	if (!game->sheeps[0].tex_sheepl.image)
		enemies_error("error loading SL_texture_xpm\n");
	else
		game->sheeps[0].tex_sheepl.addr = mlx_get_data_addr(
			game->sheeps[0].tex_sheepl.image, &game->sheeps[0].tex_sheepl.bpp, &game->sheeps[0].tex_sheepl.ll, &game->sheeps[0].tex_sheepl.e);
}

void	draw_enemies(t_game *game, t_enemy *e, t_map *m)
{
	// matrix
	e->sx = e->pos_x - m->pos_x;
	e->sy = e->pos_y - m->pos_y;
	e->sz = e->z;

	// rotation matrix
	e->cos = cos(m->a_rad);
	e->sin = sin(m->a_rad);
	e->a = e->sy * e->cos + e->sx * e->sin;
	e->b = e->sx * e->cos - e->sy * e->sin;
	e->sx = e->a;
	e->sy = e->b;
	e->sx = (e->sx * 108 / e->sy) + (game->width / 2);	// convert to screen
	e->sy = (e->sz * 108 / e->sy) + (game->world_h / 2);
	
	// if (e->sx < 0)
	// 	e->sx *= -1;
	// if (e->sy < 0) 
	// 	e->sy *= -1; 
	printf("Enemy 3d enemy pos: (%d, %d)\n", (int)e->sx, (int)e->sy);

	int h = 10;
	int w = 10;
	while (h--)
	{
		w = 10;
		while (w--)
		{
			if (e->sx > 0 && e->sx < game->world_h && e->sy > 0 && e->sy < game->width)
			my_mlx_pixel_put(&game->world, (int)e->sx + w, (int)e->sy + h, GREEN);
		}
	}
}

void	enemies_init(t_game *game, t_map *m)
{
	int	i;
	float shift;

	shift = (0.5 * game->m.m_size) - (0.5 * M_PLAYER_SIZE);
	tex_enemies_create(game);
	i = 0;
	m->y = -1;
	while (++m->y < m->rows)
	{
		m->x = -1;
		while (++m->x < m->cols)
		{
			if (m->map[m->y][m->x] == '8')
			{
				game->sheeps[i].pos_x = m->x * m->m_size + shift;
				game->sheeps[i].pos_y = m->y * m->m_size + shift;
				game->sheeps[i].z = 20;
				// printf("Enemy en pos (%d, %d)\n", m->x, m->y);
				i++;
			}
		}
	}
}
