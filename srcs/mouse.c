#include "../includes/cub3d.h"
#include "../includes/event.h"

// int	mouse_event(int button, int x, int y, t_game *game)
// {
// 	game->mo.m_x = x;
// 	game->mo.m_y = y;
// 	game->mo.button = button;
// 	printf("button = %i x = %i et y = %i\n", game->mo.button, game->mo.m_x, game->mo.m_y);
// 	printf("x1 = %i et y1 = %i  // x2 = %i et y2 = %i\n", game->p.x1, game->p.y1, game->p.x2, game->p.y2);
// 	return (0);
// }

int	mouse_press(int button, int x, int y, t_game *game)
{
	printf("button = %i x = %i et y = %i\n", button, x, y);

	if (button == M_R)
		game->left = 1;
	else if (button == M_L)
		game->right = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	printf("button2 = %i x2 = %i et y2 = %i\n", button, x, y);

	if (button == M_R)
		game->left = 0;
	else if (button == M_L)
		game->right = 0;
	return (0);
}

// int	event_mouse(t_game *game)
// {
// 		int map_offset;

// 	map_offset = ((MENU_HEIGTH - 2 * MARGIN) - game->m.h) / 2;
// 	if (game->left == 1)
// 		rotation(game, 'l');
// 	if (game->right == 1)
// 		rotation(game, 'r');
// 	if (game->weapon == 2)
// 		draw_viewfinder(game);
// 	mlx_put_image_to_window(game->mlx, game->win, game->world.image, 0, 0);
// 	mlx_put_image_to_window(game->mlx, game->win, game->map.image, game->m.w_offset, game->m.h_offset);
// 	weapon_display(game);
// 	return (0);
// }
