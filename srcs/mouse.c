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

int	mouse_move(int mx, int my, t_game *game)
{
	static int	x;

	game->left = 0;
	game->right = 0;
	mx = mx / 13;
	if (x != 0)
	{
		if ((mx >= 0 && mx < 72) && (my >= 0 && my < 670) && (x - mx) < 0)
			rotation(game, 'l');
		if ((mx >= 0 && mx < 72) && (my >= 0 && my < 670) && (x - mx) > 0)
			rotation(game, 'r');
	}
	printf("my = %i mx = %i\n", my, mx);
	x = mx;
	return (0);

	return (0);
}

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void) x;
	if (y >= 0)
	{
		if (button == M_R)
			kat_attack(game, 'p');
		else if (button == M_L)
			kat_defense(game, 'p');
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void) x;
	(void) y;
	if (button == M_R)
		kat_attack(game, 'r');
	else if (button == M_L)
		kat_defense(game, 'r');
	return (0);
}
