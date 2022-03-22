#include "../includes/cub3d.h"
#include "../includes/event.h"

int	mouse_event(int button, int x, int y, t_game *game)
{
	game->mo.m_x = x;
	game->mo.m_y = y;
	game->mo.button = button;
	printf("button = %i x = %i et y = %i\n", game->mo.button, game->mo.m_x, game->mo.m_y);
	printf("x1 = %i et y1 = %i  // x2 = %i et y2 = %i\n", game->p.x1, game->p.y1, game->p.x2, game->p.y2);
	return (0);
}

int	mouse_hook(t_game *game)
{
	if (game->mo.m_x < 479 && game->mo.m_x > 0)
		rotation(game, 'l');
	if (game->mo.m_x > 479 && game->mo.m_x < 959)
		rotation(game, 'r');
	return (0);
}
