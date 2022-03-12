#include "../../includes/cub3d.h"

static int	check_first_last_line_map(t_parse *parse, char *str)
{
	size_t	i;

	i = 0;
	while (i < (ft_strlen(str) - 1))
	{
		if (str[i] != '1' && str[i] != ' ')
		{
			ft_error(parse, "The map is not close.\n", NULL);
			exit(0);
		}
		i++;
	}
	return (1);
}

static int	check_map_close(t_parse *parse, char *str)
{
	int			i;
	static int	j = 0;

	i = 0;
	if (++j == 1)
		check_first_last_line_map(parse, str);
	else if (j == parse->m_height)
		check_first_last_line_map(parse, str);
	while (str[i] == ' ')
		i++;
	if (str[i] != '1' || str[ft_strlen(str) - 2] != '1')
	{
		ft_error(parse, "The map is not close.\n", NULL);
		exit(0);
	}
	else
		return (1);
}

//check si la map contient que des valeurs voulues.
int	ft_is_map(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	if ((ft_charinstr(line, '1') == 1) || (ft_charinstr(line, '0') == 1))
	{
		while (line[i])
		{
			if (line[i] != '1' && line[i] != '0' && line[i] != '2' && \
				line[i] != 'N' && line[i] != 'E' && line[i] != 'S' && \
				line[i] != 'W' && line[i] != '\n' && line[i] != '\t' && \
				line[i] != ' ')
				return (2);
			i++;
		}
		return (1);
	}
	return (0);
}

//permet de calculer la taille de la map pour la malloqué.
int	ft_map(char *line, t_parse *parse)
{
	int			i;
	static int	nblines = 0;
	static int	ssizeline = 0;

	i = 0;
	if (ft_is_map(line) == 1 && check_missing(parse) == 0)
	{
		nblines += 1;
		i = ft_strlen(line);
		if (i > ssizeline)
			ssizeline = i;
	}
	parse->m_height = nblines;
	parse->m_width = ssizeline - 1;
	return (0);
}

//permet de malloqué la map et la save dans la struct (char **map)
int	get_map(t_parse *parse, const char *map)
{
	int		fd;
	int		i;
	char	*line;
	int		l;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	parse->map = malloc(sizeof(char *) * (parse->m_height + 1));
	parse->map[parse->m_height] = NULL;
	i = 0;
	while (line != NULL)
	{
		if (ft_is_map(line) == 1)
		{
			check_map_close(parse, line);
			parse->map[i] = malloc((parse->m_width + 2) * sizeof(char));
			l = ft_strlen(line);
			ft_strlcpy(parse->map[i], line, l + 1);
			replace_space_tab(parse->map[i]);
			if (l != parse->m_width + 1)
			{
				ft_memset((void *)&parse->map[i][l - 1], '1', parse->m_width + 1 - l);
				parse->map[i][parse->m_width] = '\n';
				parse->map[i][parse->m_width + 1] = '\0';
			}
			i++;
		}
		free(line);
		line = get_next_line(fd);
	}
	print_map(parse->map);
	return (0);
}
