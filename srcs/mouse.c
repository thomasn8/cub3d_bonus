#include "../includes/cub3d.h"
#include "../includes/event.h"

int	mouse_move(int mx, int my, t_game *game)
{
	static int x;

	(void)	my;
	game->left = 0;
	game->right = 0;
	mx = mx / 13;
	if (x != 0)
	{
		if (x - mx < 0)
			rotation(game, 'l');
		if (x - mx > 0)
			rotation(game, 'r');
	}
	printf("x = %i mx = %i\n", x, mx);
	x = mx;
	return (0);
}
