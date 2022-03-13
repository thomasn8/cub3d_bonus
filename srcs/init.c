#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*pixel;

	pixel = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
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
	game->menu.image = mlx_xpm_file_to_image(game->mlx, "./images/keyboard_w", &game->menu.width, &game->menu.heigth);
	if (game->menu.image)
	{
		game->menu.addr = mlx_get_data_addr(game->menu.image, &game->menu.bits_per_pixel, &game->menu.line_length, &game->menu.endian);
		mlx_put_image_to_window(game->mlx, game->win, game->menu.image, 260, HEIGTH - 85);
	}
	mlx_string_put(game->mlx, game->win, 280 + 0, HEIGTH - 35, MENU_TEXT_COLOR, "move");
	mlx_string_put(game->mlx, game->win, 280 + 140, HEIGTH - 35, MENU_TEXT_COLOR, "turn");
	mlx_string_put(game->mlx, game->win, 280 + 257, HEIGTH - 35, MENU_TEXT_COLOR, "use");
	mlx_string_put(game->mlx, game->win, 280 + 346, HEIGTH - 35, MENU_TEXT_COLOR, "map");
	mlx_string_put(game->mlx, game->win, 280 + 439, HEIGTH - 35, MENU_TEXT_COLOR, "quit");
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
