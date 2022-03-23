/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: desa <desa@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:39:50 by desa              #+#    #+#             */
/*   Updated: 2022/03/23 16:39:52 by desa             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

static int	check_map(t_parse *parse, char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if ((ft_isdigit(map[y][x]) != 1) && map[y][x] != 'N' && \
			map[y][x] != 'E' && map[y][x] != 'S' && \
			map[y][x] != 'W' && map[y][x] != '\n')
				ft_error(parse, "wrong char in map", NULL);
		}
	}
	return (0);
}

static int	check_missing_in_map(t_parse *parse)
{
	if (parse->wall == 0)
		ft_error(parse, "Missing wall (1)", NULL);
	else if (parse->free_space == 0)
		ft_error(parse, "Missing free space (0)", NULL);
	else if (parse->check_player == 0)
		ft_error(parse, "Missing player (N or E or S or W)", NULL);
	return (0);
}

static int	check_player2(int x, int y, t_parse *parse)
{
	if (parse->check_player == 1)
		ft_error(parse, "To many player", NULL);
	parse->check_player = 1;
	parse->view_player = parse->map[y][x];
	parse->start_x = x;
	parse->start_y = y;
	return (0);
}

static int	check_player(t_parse *parse)
{
	size_t	x;
	size_t	y;

	y = -1;
	while (parse->map[++y])
	{
		x = -1;
		while (parse->map[y][++x])
		{
			if (parse->map[y][x] == '1')
				parse->wall = 1;
			else if (parse->map[y][x] == '0')
				parse->free_space = 1;
			else if (parse->map[y][x] == 'E' || parse->map[y][x] == 'S' \
					|| parse->map[y][x] == 'N' || parse->map[y][x] == 'W')
				check_player2(x, y, parse);
		}
	}
	check_missing_in_map(parse);
	return (0);
}

// parsing des couleurs à améliorer utiliser des int ou des char ?
int	parsing(int fd, const char *map, t_parse *parse)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		check_missing(parse);
		parse_textures_colors(line, parse);
		if (parse->error == 0 && ((ft_charinstr(line, '1') == 1) || \
		(ft_charinstr(line, '0') == 1)))
			ft_map(line, parse);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	check_error(parse);
	get_map(parse, map);
	check_map(parse, parse->map);
	check_player(parse);
	return (0);
}
