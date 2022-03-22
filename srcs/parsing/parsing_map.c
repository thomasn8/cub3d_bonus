#include "../../includes/cub3d.h"

static int	check_map_space(t_parse *parse, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == '0')
			{
				if (map[y][x + 1] == ' ' || map[y][x - 1] == ' ')
					ft_error(parse, "map is not close. (1)", NULL);
				if (map[y - 1][x] == ' ' || map[y + 1][x] == ' ')
					ft_error(parse, "map is not close. (1.1)", NULL);
			}
		}
	}
	return (0);
}

static int	check_first_last_line_map(t_parse *parse, char *str)
{
	size_t	i;

	i = 0;
	while (i < (ft_strlen(str) - 1))
	{
		if (str[i] != '1' && str[i] != ' ')
		{
			ft_error(parse, "The map is not close. (2)", NULL);
			exit(0);
		}
		i++;
	}
	return (1);
}

int	check_map_close(t_parse *parse, char *str)
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
		ft_error(parse, "The map is not close. (3)", NULL);
		exit(0);
	}
	else
		return (1);
}

void	get_map2(int l, int i, t_parse *parse)
{
	if (l < parse->m_width)
	{
		ft_memset((void *)&parse->map[i][l - 1], ' ', parse->m_width + 1 - l);
		parse->map[i][parse->m_width] = '\n';
		parse->map[i][parse->m_width + 1] = '\0';
	}
}

//permet de malloqué la map et la save dans la struct (char **map)
void	get_map(t_parse *parse, const char *map)
{
	int		fd;
	int		i;
	char	*line;
	int		l;

	fd = open(map, O_RDONLY);
	line = get_next_line(fd);
	parse->map = malloc(sizeof(char *) * (parse->m_height + 1));
	parse->map[parse->m_height] = NULL;
	i = -1;
	while (line != NULL)
	{
		if (parse_textures(line) == 0 && \
		((ft_charinstr(line, '1') == 1) || (ft_charinstr(line, '0') == 1)))
		{
			check_map_close(parse, line);
			parse->map[++i] = malloc((parse->m_width + 1) * sizeof(char));
			l = ft_strlen(line);
			ft_strlcpy(parse->map[i], line, l + 1);
			get_map2(l, i, parse);
		}
		free(line);
		line = get_next_line(fd);
	}
	check_map_space(parse, parse->map);
	replace_space_tab(parse->map);
	print_map(parse->map);
}
