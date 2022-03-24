/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:03:19 by desa              #+#    #+#             */
/*   Updated: 2022/03/24 21:03:25 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/event.h"

int	mouse_press(int button, int x, int y, t_game *game)
{
	(void) x;
	(void) y;
	weapon_press(button, game);
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void) x;
	(void) y;
	weapon_release(button, game);
	return (0);
}

int	mouse_move(int mx, int my, t_game *game)
{
	static int	x;

	game->left = 0;
	game->right = 0;
	mx = mx / 15;
	if (x != 0)
	{
		printf("mx: %d / my: %d\n", mx, my);
		if ((mx >= 0 && mx < game->mouse_x) && (my >= 0 && my < game->mouse_y) && (x - mx) < 0)
			rotation(game, 'l');
		if ((mx >= 0 && mx < game->mouse_x) && (my >= 0 && my < game->mouse_y) && (x - mx) > 0)
			rotation(game, 'r');
	}
	x = mx;
	return (0);
}
