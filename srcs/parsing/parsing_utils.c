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

void	replace_space_tab(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = '1';
		else if (str[i] == ' ')
			str[i] = '1';
		i++;
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
	int x;

	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
			write(1, &map[y][x], 1);
	}
}

void	print_all(t_parse *p)
{
	printf("no = %s\n", p->no);
	printf("so = %s\n", p->so);
	printf("we = %s\n", p->we);
	printf("ea = %s\n", p->ea);
	printf("view_player = %c\n", p->view_player);
	printf("start_x = %i\n", p->start_x);
	printf("start_y = %i\n", p->start_y);
	printf("m_height = %i\n", p->m_height);
	printf("m_width = %i\n", p->m_width);
	printf("c_f = %s\n", p->c_f);
	printf("c_s = %s\n", p->c_s);
	printf("hex_f = %lu\n", p->hex_f);
	printf("hex_s = %lu\n", p->hex_s);
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
