#include "../../includes/cub3d.h"

static void	get_color(int nbr, int sum, t_parse *parse, char c)
{
	if (nbr == 1)
		parse->r = sum;
	else if (nbr == 2)
		parse->g = sum;
	else if (nbr == 3)
		parse->b = sum;
	if (parse->r != -1 && parse->g != -1 && parse->b != -1 && c == 'F')
		parse->hex_f = create_rgb(0, parse->r, parse->g, parse->b);
	else if (parse->r != -1 && parse->g != -1 && parse->b != -1 && c == 'S')
		parse->hex_s = create_rgb(0, parse->r, parse->g, parse->b);
}

void	check_color(t_parse *parse, char *color, char c)
{
	int		i;
	int		sum;
	int		nbr;

	nbr = 0;
	sum = 0;
	i = 0;
	while (color[i] != '\0')
	{
		while (color[i] >= '0' && color[i] <= '9')
		{
			sum = (sum * 10) + (color[i] - 48);
			if (sum > 255)
				ft_error(parse, "Max int colors (255)", NULL);
			i++;
		}
		if (sum >= 0 && sum <= 255)
			nbr++;
		if (nbr > 3)
			ft_error(parse, "values colors (F) or (C)", NULL);
		get_color(nbr, sum, parse, c);
		sum = 0;
		if (ft_isprint(color[i]))
			i++;
	}
}

char	*save_args(char *line)
{
	int		i;
	int		len;
	int		start;
	char	*temp;

	i = 2;
	len = 0;
	start = 2;
	while (!ft_notblank(line[i]))
	{
		i++;
		start++;
	}
	while (line[i] != '\n')
	{
		i++;
		len++;
	}
	temp = ft_substr(line, start, len);
	return (temp);
}

int	parse_textures(char *line)
{
	if (line[0] == 'N' && (line[1] == 'O' || line[1] == ' '))
		return (1);
	else if (line[0] == 'S' && (line[1] == 'O' || line[1] == ' '))
		return (2);
	else if (line[0] == 'W' && (line[1] == 'E' || line[1] == ' '))
		return (3);
	else if (line[0] == 'E' && (line[1] == 'A' || line[1] == ' '))
		return (4);
	else if (line[0] == 'F')
		return (5);
	else if (line[0] == 'C')
		return (6);
	return (0);
}

// parsing des textures (images que l'on va afficher sur les murs)
int	parse_textures_colors(char *line, t_parse *parse)
{
	if (parse_textures(line) == 1 && parse->no == NULL)
		parse->no = save_args(line);
	else if (parse_textures(line) == 2 && parse->so == NULL)
		parse->so = save_args(line);
	else if (parse_textures(line) == 3 && parse->we == NULL)
		parse->we = save_args(line);
	else if (parse_textures(line) == 4 && parse->ea == NULL)
		parse->ea = save_args(line);
	else if (parse_textures(line) == 5 && parse->c_f == NULL)
	{
		parse->c_f = save_args(line);
		check_color(parse, parse->c_f, 'F');
	}
	else if (parse_textures(line) == 6 && parse->c_s == NULL)
	{
		parse->c_s = save_args(line);
		check_color(parse, parse->c_s, 'C');
	}
	return (0);
}
