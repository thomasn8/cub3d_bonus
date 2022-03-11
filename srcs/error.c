#include "../includes/cub3d.h"

int	check_missing(t_parse *parse)
{
	if (parse->no == NULL || parse->so == NULL || \
		parse->we == NULL || parse->ea == NULL)
		ft_error(parse, "Il manque une texture.", NULL);
	else if (parse->c_f == NULL || parse->c_s == NULL)
		ft_error(parse, "Il manque une couleur.", NULL);
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
