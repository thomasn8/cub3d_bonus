#include "../../includes/cub3d.h"

void	check_error(t_parse *parse)
{
	if (parse->error == 1)
		ft_error(parse, "missing textures\n", NULL);
	else if (parse->error == 2)
		ft_error(parse, "missing colors\n", NULL);
	else if (parse->error == 3)
		ft_error(parse, "The map is not close.\n", NULL);
}

int	check_missing(t_parse *parse)
{
	if (parse->no == NULL || parse->so == NULL || \
		parse->we == NULL || parse->ea == NULL)
		parse->error = 1;
	else if (parse->c_f == NULL || parse->c_s == NULL)
		parse->error = 2;
	else
		parse->error = 0;
	return (0);
}

int	ft_error(t_parse *parse, char *str, char *line)
{
	if (str)
		write_errors(str);
	if (parse)
		free_all(parse);
	if (line)
		free(line);
	exit(0);
}

int	check_name(char *map, char *correct_ext)
{
	char	*ext;

	ext = ft_strrchr(map, '.');
	if (ext == NULL)
		return (0);
	if ((ft_strncmp(ext, correct_ext, ft_strlen(ext)) == 0))
		return (1);
	return (0);
}

void	save_map(const char *map, t_parse *parse)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		write_errors("The file is not open\n");
		exit (0);
	}
	initialisation(parse);
	parsing(fd, map, parse);
}
