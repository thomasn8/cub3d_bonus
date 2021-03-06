/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:54:48 by tnanchen          #+#    #+#             */
/*   Updated: 2022/03/24 19:59:24 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/event.h"

int	main(int ac, char **av)
{
	t_game	game;
	t_parse	parse;

	if (ac != 2)
		ft_error(NULL, " argument", NULL);
	if (!check_name(av[1], ".cub"))
		ft_error(NULL, "Nom de la map invalid\n ext == [.cub]\n", NULL);
	save_map(av[1], &parse);
	window_init(&game);
	game_init(&game);
	world_init(&game);
	minimap_init(&game, &parse);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, key_release, &game);
	mlx_hook(game.win, X_EVENT_MOUSE_PRESS, 0, mouse_press, &game);
	mlx_hook(game.win, X_EVENT_MOUSE_RELEASE, 0, mouse_release, &game);
	mlx_hook(game.win, 6, 1L << 8, mouse_move, &game);
	mlx_hook(game.win, X_EVENT_EXIT, 0, quit_prog, &game);
	mlx_loop_hook(game.mlx, events_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
