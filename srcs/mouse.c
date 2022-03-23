/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desa <desa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 17:03:19 by desa              #+#    #+#             */
/*   Updated: 2022/03/23 17:03:20 by desa             ###   ########.fr       */
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
		if ((mx >= 0 && mx < 72) && (my >= 0 && my < 670) && (x - mx) < 0)
			rotation(game, 'l');
		if ((mx >= 0 && mx < 72) && (my >= 0 && my < 670) && (x - mx) > 0)
			rotation(game, 'r');
	}
	x = mx;
	return (0);
}
