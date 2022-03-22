#include "../includes/cub3d.h"
#include "../includes/event.h"

int	mouse_move(int mx, int my, t_game *game)
{
	static int x;

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
}
