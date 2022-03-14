#include "../includes/cub3d.h"
#include "../includes/event.h"

int	quit_prog(t_game *game)
{
	printf("Program left properly.\n");
	mlx_clear_window(game->mlx, game->win);
	mlx_destroy_window(game->mlx, game->win);
	exit(0);
}

int	key_press(int keycode, t_game *game)
{
	if (keycode == K_W)
		game->w = 1;
	else if (keycode == K_S)
		game->s = 1;
	else if (keycode == K_A)
		game->a = 1;
	else if (keycode == K_D)
		game->d = 1;
	else if (keycode == K_LEFT)
		game->left = 1;
	else if (keycode == K_RIGHT)
		game->right = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == K_W)
		game->w = 0;
	else if (keycode == K_S)
		game->s = 0;
	else if (keycode == K_A)
		game->a = 0;
	else if (keycode == K_D)
		game->d = 0;
	else if (keycode == K_LEFT)
		game->left = 0;
	else if (keycode == K_RIGHT)
		game->right = 0;
	else if (keycode == K_ESC)
		quit_prog(game);
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
	mlx_put_image_to_window(game->mlx, game->win, game->world.image, 0, 0);
	mlx_put_image_to_window(game->mlx, game->win, game->map.image, game->m.w_offset, game->m.h_offset);
	return (0);
}
