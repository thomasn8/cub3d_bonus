#include "../../includes/cub3d.h"

void	initialisation(t_parse *parse)
{
	parse->map = NULL;
	parse->no = NULL;
	parse->so = NULL;
	parse->we = NULL;
	parse->ea = NULL;
	parse->view_player = 0;
	parse->m_height = 0;
	parse->m_width = 0;
	parse->c_f = NULL;
	parse->c_s = NULL;
	parse->error = 0;
	parse->check_player = 0;
	parse->wall = 0;
	parse->free_space = 0;
	parse->start_x = 0;
	parse->start_y = 0;
	parse->r = -1;
	parse->g = -1;
	parse->b = -1;
	parse->rgb = -1;
}

void	replace_space_tab(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (map[y][x] == ' ')
				map[y][x] = '1';
		}
	}
}

void	free_all(t_parse *parse)
{
	if (parse->map != NULL)
		ft_free_array((void **)parse->map);
	if (parse->no)
		free(parse->no);
	if (parse->ea)
		free(parse->ea);
	if (parse->we)
		free(parse->we);
	if (parse->so)
		free(parse->so);
	if (parse->c_f)
		free(parse->c_f);
	if (parse->c_s)
		free(parse->c_s);
}

void	print_map(char **map)
{
	int	y;
	int	x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			write(1, &map[y][x], 1);
	}
}

//permet de calculer la taille de la map pour la malloqué.
int	ft_map(char *line, t_parse *parse)
{
	int			i;
	static int	nblines = 0;
	static int	ssizeline = 0;

	i = 0;
	nblines += 1;
	i = ft_strlen(line);
	if (i > ssizeline)
		ssizeline = i;
	parse->m_height = nblines;
	parse->m_width = ssizeline - 1;
	return (0);
}
