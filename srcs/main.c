#include "../includes/cub3d.h"
#include "../includes/event.h"

static int	check_map_name(char *map)
{
	char	*ext;
	char	*correct_ext;

	correct_ext = ".cub";
	ext = ft_strrchr(map, '.');
	if (ext == NULL)
		return (0);
	if ((ft_strncmp(ext, correct_ext, ft_strlen(ext)) == 0))
		return (1);
	return (0);
}

static void	save_map(const char *map, t_parse *parse)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		write_errors("The file is not open\n");
		exit (0);
	}
	else
		parsing(fd, map, parse);
}

int	main(int ac, char **av)
{
	t_game	game;
	t_parse	*parse;

	parse = malloc(sizeof(t_parse));
	initialization(parse);
	if (ac == 2)
	{
		if (check_map_name(av[1]) == 1)
		{
			save_map(av[1], parse);
			params_init(&game);
			menu_init(&game);
			world_init(&game);
			minimap_init(&game, parse);
			mlx_hook(game.win, X_EVENT_KEY_PRESS, 0, key_press, &game);
			mlx_hook(game.win, X_EVENT_KEY_RELEASE, 0, key_release, &game);
			mlx_hook(game.win, X_EVENT_EXIT, 0, quit_prog, &game);
			mlx_loop_hook(game.mlx, events_loop, &game);
			mlx_loop(game.mlx);
		}
		else
			ft_error(parse, "Nom de la map invalid\n ext == [.cub]\n", NULL);
	}
	else
		write_errors("Missing arguments [.cub]");
	return (0);
}
