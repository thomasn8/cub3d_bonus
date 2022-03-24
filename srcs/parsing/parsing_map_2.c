/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_map_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 16:40:32 by desa              #+#    #+#             */
/*   Updated: 2022/03/24 07:40:30 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	get_map3(t_parse *parse)
{
	check_map_space(parse, parse->map);
	replace_space_tab(parse->map);
	print_map(parse->map);
<<<<<<< HEAD
	parse->m_width -= 1;
=======
	parse->m_width -= 1;											// et je le retirais de la width à la fin, après traitement
>>>>>>> origin/thomas
}
