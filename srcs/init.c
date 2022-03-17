#include "../includes/cub3d.h"
#include "../includes/map.h"

void	textures_init(t_rays *r, t_game *game)
{
	r->tex_n.image = mlx_xpm_file_to_image(game->mlx, game->m.no, &r->tex_n.width, &r->tex_n.heigth);
	if (r->tex_n.image)
		r->tex_n.addr = mlx_get_data_addr(r->tex_n.image, &r->tex_n.bits_per_pixel, &r->tex_n.line_length, &r->tex_n.endian);
	else
		write(2, "Error: downloading NO_texture_xpm\n", 34);
	r->tex_s.image = mlx_xpm_file_to_image(game->mlx, game->m.so, &r->tex_s.width, &r->tex_s.heigth);
	if (r->tex_s.image)
		r->tex_s.addr = mlx_get_data_addr(r->tex_s.image, &r->tex_s.bits_per_pixel, &r->tex_s.line_length, &r->tex_s.endian);
	else
		write(2, "Error: downloading SO_texture_xpm\n", 34);
	r->tex_e.image = mlx_xpm_file_to_image(game->mlx, game->m.ea, &r->tex_e.width, &r->tex_e.heigth);
	if (r->tex_e.image)
		r->tex_e.addr = mlx_get_data_addr(r->tex_e.image, &r->tex_e.bits_per_pixel, &r->tex_e.line_length, &r->tex_e.endian);
	else
		write(2, "Error: downloading EA_texture_xpm\n", 34);
	r->tex_w.image = mlx_xpm_file_to_image(game->mlx, game->m.we, &r->tex_w.width, &r->tex_w.heigth);
	if (r->tex_w.image)
		r->tex_w.addr = mlx_get_data_addr(r->tex_w.image, &r->tex_w.bits_per_pixel, &r->tex_w.line_length, &r->tex_w.endian);
	else
		write(2, "Error: downloading WE_texture_xpm\n", 34);
}

void	minimap_init(t_game *game, t_parse *parse)
{
	game->m.ws_fps = 1.2;
	game->m.ad_fps = 0.75;
	game->m.rot_fps = 7;
	map_description(game, parse);
	textures_init(&game->r, game);
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
	// game->menu.image = mlx_xpm_file_to_image(game->mlx, "./images/keyboard_w", &game->menu.width, &game->menu.heigth);
	// if (game->menu.image)
	// {
	// 	game->menu.addr = mlx_get_data_addr(game->menu.image, &game->menu.bits_per_pixel, &game->menu.line_length, &game->menu.endian);
	// 	mlx_put_image_to_window(game->mlx, game->win, game->menu.image, 260, HEIGTH - 85);
	// }
	// mlx_string_put(game->mlx, game->win, 280 + 0, HEIGTH - 35, MENU_TEXT_COLOR, "move");
	// mlx_string_put(game->mlx, game->win, 280 + 140, HEIGTH - 35, MENU_TEXT_COLOR, "turn");
	// mlx_string_put(game->mlx, game->win, 280 + 257, HEIGTH - 35, MENU_TEXT_COLOR, "use");
	// mlx_string_put(game->mlx, game->win, 280 + 346, HEIGTH - 35, MENU_TEXT_COLOR, "map");
	// mlx_string_put(game->mlx, game->win, 280 + 439, HEIGTH - 35, MENU_TEXT_COLOR, "quit");
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
