#include "../includes/cub3d.h"
#include "../includes/minimap.h"

// code pour voir les bords du miniplayer
static void	draw_player_pos(t_image *image, int pos_x, int pos_y, int color)
{
	t_mini_player 	player;

	player.width = 0;
	player.height = 0;
	if (color == MINI_BG_COLOR)
	{
		while (player.height < MINI_PLAYER_SIZE)
		{
			while (player.width < MINI_PLAYER_SIZE)
				my_mlx_pixel_put(image, pos_x + player.width++, pos_y + player.height, color);
			player.width = 0;
			player.height++;
		}
	}
	else
	{
		while (player.height < MINI_PLAYER_SIZE)
		{
			while (player.width < MINI_PLAYER_SIZE)
			{
				if (player.width == 0 || player.height == 0 || player.width == MINI_PLAYER_SIZE - 1 || player.height == MINI_PLAYER_SIZE - 1)
					my_mlx_pixel_put(image, pos_x + player.width++, pos_y + player.height, 0x000000FF);
				else
					my_mlx_pixel_put(image, pos_x + player.width++, pos_y + player.height, color);
			}
			player.width = 0;
			player.height++;
		}
	}
}

void	draw_line(t_image *image, int x1, int y1, int x2, int y2)
{
	double	delta_x;
	double	delta_y;
	int		pixels;
	double	pixel_x;
	double	pixel_y;

	delta_x = x2 - x1;
	delta_y = y2 - y1;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = x1;
	pixel_y = y1;
	while (pixels)
	{
		my_mlx_pixel_put(image, pixel_x, pixel_y, MINI_PLAYER_COLOR);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}

void draw_minimap(t_image *image)
{
	int x;
	int y;
	int xo;
	int yo;
	int color;
	char c;
	char **minimap;

	minimap = ft_split(map, '\n');
	y = 0;
	x = 0;
	while (y < mapY)
	{
		while (x < mapX)
		{
			if (minimap[y][x] == '1')
				color = MINI_WALL_COLOR;
			else
				color = MINI_SPACE_COLOR;
			xo = (x+1) * mapS;
			yo = (y+1) * mapS;
			while (yo > y * mapS)
			{
				yo--;
				while (xo > x * mapS)
				{
					xo--;
					my_mlx_pixel_put(image, xo, yo, color);
				}
				xo = (x+1) * mapS;
			}
			x++;
		}
		x = 0;
		y++;
	} 
}

char	*int_to_hexa(unsigned int nbr)
{
	unsigned int		nbr_cpy;
	char				*buf;
	int					size;

	if (nbr == 0)
	{
		buf = malloc(3 * sizeof(char));
		buf[0] = '0';
		buf[1] = '0';
		buf[2] = 0;
		return (buf);
	}
	nbr_cpy = nbr;
	size = 1;
	nbr_cpy /= 16;
	while (nbr_cpy)
	{
		nbr_cpy /= 16;
		size++;
	}
	buf = malloc(size * sizeof(char));
	if (!buf)
		return (NULL);
	buf[size--] = 0;
	while (nbr)
	{
		buf[size--] = "0123456789ABCDEF"[nbr % 16];
		nbr /= 16;
	}
	return (buf);
}

char *get_hex_color(unsigned int color)
{
	char *hexa;
	char *t;
	char *tmp;

	t = int_to_hexa((color >> 24) & 0xFF);
	tmp = int_to_hexa(color);
	hexa = ft_strjoin3("0x", t, tmp);
	free(tmp);
	free(t);
	return (hexa);
}