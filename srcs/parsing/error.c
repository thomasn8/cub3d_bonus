#include "../../includes/cub3d.h"

int	check_missing(t_parse *parse)
{
	if (parse->no == NULL || parse->so == NULL || \
		parse->we == NULL || parse->ea == NULL)
		ft_error(parse, "Il manque une texture.", NULL);
	else if (parse->c_f == NULL || parse->c_s == NULL)
		ft_error(parse, "Il manque une couleur.", NULL);
	return (0);
}

int	check_error_texture(t_parse *parse, char *textures)
{
	int		i;

	i = 2;
	while (!ft_notblank(textures[i]))
		i++;
	if (textures[i] != '.' && textures[i + 1] != '/')
		ft_error(parse, "Is not a pass", NULL);
	if (!check_name(textures, ".xpm\n"))
		ft_error(parse, "Is not correct file (.xpm)", NULL);
	return (1);
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
