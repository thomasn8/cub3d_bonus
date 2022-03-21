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

void	enemies_init(t_game *game, t_map *m)
{
	int	i;

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
				game->sheeps[i].mx = m->x;
				game->sheeps[i].my = m->y;
				i++;
				// printf("Enemy en pos (%d, %d)\n", m->x, m->y);
			}
		}
	}
}
