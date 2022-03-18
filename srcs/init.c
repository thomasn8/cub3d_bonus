#include "../includes/cub3d.h"
#include "../includes/map.h"

void	minimap_init(t_game *game, t_parse *parse)
{
	game->m.ws_fps = 1.2;
	game->m.ad_fps = 0.75;
	game->m.rot_fps = 7;
	map_description(game, parse);
	v_textures_init(&game->r, game);
	h_textures_init(&game->r, game);
	player_description(game, parse);
	game->m.y = -1;
	color_map(&game->map, &game->m);
	game->m.clean_map = copy_map(&game->map, game->m.w, game->m.h);
	draw_all(game, '1');
}

void	world_init(t_game *game)
{
	int x;
	int y;

	game->world.image = mlx_new_image(game->mlx, game->width, game->world_h);
	game->world.addr = mlx_get_data_addr(game->world.image, &game->world.bits_per_pixel, &game->world.line_length, &game->world.endian);
	y = -1;
	while (++y < game->world_h)
	{
		x = -1;
		while (++x < game->width)
			my_mlx_pixel_put(&game->world, x, y, WORLD_COLOR);
	}
	game->r.r_1 = FOV * M_RAY_FACTOR;
	game->r.r_05 = game->r.r_1 / 2;
	game->r.r_ra = (M_1_DEG_RAD / M_RAY_FACTOR);
	game->r.fov_05 = game->r.r_05 * game->r.r_ra;
}

void	menu_init(t_game *game)
{
	int 	x;
	int 	y;

	y = -1 + game->world_h;
	while (++y < game->heigth)
	{
		x = -1;
		while (++x < game->width)
			mlx_pixel_put(game->mlx, game->win, x, y, MENU_COLOR);
	}
	mlx_string_put(game->mlx, game->win, WIDTH - 60, HEIGTH - 30, MENU_TEXT_COLOR, "CUB3D");
}

void	params_init(t_game *game)
{
	game->mlx = mlx_init();
	game->width = WIDTH;
	game->heigth = HEIGTH;
	game->world_h = HEIGTH - MENU_HEIGTH;
	game->win = mlx_new_window(game->mlx, game->width, game->heigth, "cub3d");
	game->w = 0;
	game->s = 0;
	game->a = 0;
	game->d = 0;
	game->left = 0;
	game->right = 0;
}
