#include "../../includes/cub3d.h"

// parsing des couleurs à améliorer utiliser des int ou des char ?
int	parsing(int fd, const char *map, t_parse *parse)
{
	char	*line;
	
	line = get_next_line(fd);
	while (line != NULL)
	{
		parse_textures_colors(line, parse);
		ft_map(line, parse);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	check_missing(parse);
	get_map(parse, map);
	return (0);
}
