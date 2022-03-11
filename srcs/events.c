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
	else if (keycode == K_M && game->minimap == 0)
		game->minimap = 1;
	else if (keycode == K_M && game->minimap == 1)
		game->minimap = 0;
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
	if (game->w == 1)
		miniplayer_move(&game->map, 'w', &game->m);
	if (game->s == 1)
		miniplayer_move(&game->map, 's', &game->m);
	if (game->a == 1)
		miniplayer_move(&game->map, 'a', &game->m);
	if (game->d == 1)
		miniplayer_move(&game->map, 'd', &game->m);
	if (game->left == 1)
		miniplayer_rotation(&game->map, 'l', &game->m);
	if (game->right == 1)
		miniplayer_rotation(&game->map, 'r', &game->m);
	if (game->minimap == 1)
	{
		mlx_put_image_to_window(game->mlx, game->win, game->world.image, 0, 0);
		mlx_put_image_to_window(game->mlx, game->win, game->map.image, MARGIN, MARGIN);
	}
	else
		mlx_put_image_to_window(game->mlx, game->win, game->world.image, 0, 0);
	return (0);
}
