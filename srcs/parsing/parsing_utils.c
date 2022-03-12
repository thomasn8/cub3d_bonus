#include "../../includes/cub3d.h"

void	initialization(t_parse *parse)
{
	parse->map = NULL;
	parse->no = NULL;
	parse->so = NULL;
	parse->we = NULL;
	parse->ea = NULL;
	parse->start_player = 0;
	parse->m_height = 0;
	parse->m_width = 0;
	parse->c_f = NULL;
	parse->c_s = NULL;
	parse->error = 0;
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
	if (parse->map)
		ft_free_array(parse->map);
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
	if (parse)
		free(parse);
}

void	print_map(char **grid)
{
	int	y;
	int x;

	y = -1;
	while (grid[++y])
	{
		x = -1;
		while (grid[y][++x])
			write(1, &grid[y][x], 1);
	}
}
