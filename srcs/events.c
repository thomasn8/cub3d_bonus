#include "../includes/cub3d.h"
#include "../includes/event.h"

void	my_mlx_pixel_put(t_image *image, int x, int y, int color)
{
	char	*pixel;

	pixel = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	*(unsigned int *)pixel = color;
}

int	quit_prog(t_game *game)
{
	ft_free_array((void **)game->m.clean_map);
	free_all(game->parse);
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	printf("Program left properly.\n");
	exit(0);
}

int	key_press(int k, t_game *game)
{
	if (k == K_W)
		game->w = 1;
	else if (k == K_S)
		game->s = 1;
	else if (k == K_A)
		game->a = 1;
	else if (k == K_D)
		game->d = 1;
	else if (k == K_LEFT)
		game->left = 1;
	else if (k == K_RIGHT)
		game->right = 1;
	else
		weapon_press(k, game);
	return (0);
}

int	key_release(int k, t_game *game)
{
	if (k == K_W)
		game->w = 0;
	else if (k == K_S)
		game->s = 0;
	else if (k == K_A)
		game->a = 0;
	else if (k == K_D)
		game->d = 0;
	else if (k == K_LEFT)
		game->left = 0;
	else if (k == K_RIGHT)
		game->right = 0;
	else if (k == K_E)
		interaction(game);
	else if (k == K_ESC)
		quit_prog(game);
	else
		weapon_release(k, game);
	return (0);
}

int	events_loop(t_game *game)
{
	int map_offset;

	map_offset = ((MENU_HEIGTH - 2 * MARGIN) - game->m.h) / 2;
	if (game->w == 1)
		move(game, 'w');
	if (game->s == 1)
		move(game, 's');
	if (game->a == 1)
		move(game, 'a');
	if (game->d == 1)
		move(game, 'd');
	if (game->left == 1)
		rotation(game, 'l');
	if (game->right == 1)
		rotation(game, 'r');
	if (game->weapon == 2)
		draw_viewfinder(game);
	mlx_put_image_to_window(game->mlx, game->win, game->world.image, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->map.image, game->m.w_offset, game->m.h_offset);
	weapon_display(game);
	return (0);
}
