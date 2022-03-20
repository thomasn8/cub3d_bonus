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
	else if (keycode == K_UP)
		attack(game);
	else if (keycode == K_DOWN)
		defense(game);
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
	else if (keycode == K_E)
		interaction(game);
	else if (keycode == K_1)
		game->weapon = 1;
	else if (keycode == K_2)
		game->weapon = 2;
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
	if (game->weapon == 1 && game->state == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_weapon1_run.image, game->m.w_offset + 75, game->world_h - game->tex_weapon1_run.heigth);
	else if (game->weapon == 2 && game->state == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_weapon2_run.image, game->m.w_offset + 75, game->world_h - game->tex_weapon2_run.heigth);
	return (0);
}
