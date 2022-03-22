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
	params_init(&game);
	menu_init(&game);
	world_init(&game);
	minimap_init(&game, &parse);
	mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, key_press, &game);
	mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, key_release, &game);
	mlx_hook(game.win, X_EVENT_EXIT, 0, quit_prog, &game);
	mlx_mouse_hook(game.win, mouse_event, &game);
	mlx_loop_hook(game.mlx, mouse_hook, &game);
	mlx_loop_hook(game.mlx, events_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
