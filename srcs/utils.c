/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:51:46 by tnanchen          #+#    #+#             */
/*   Updated: 2022/03/24 07:54:54 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/map.h"

float	deg_to_rad(int angle)
{
	return (angle * PI / 180);
}

int	rad_to_deg(float angle)
{
	return (angle / PI * 180);
}

unsigned int	get_color_value(t_image *image, int x, int y)
{
	char	*ptr;

	ptr = image->addr + (y * image->line_length
			+ x * (image->bits_per_pixel / 8));
	return (*(unsigned int *)ptr);
}

unsigned int	get_tex_color(t_img *tex, int x, int y, float shade)
{
	unsigned int	clr;
	int				t;
	int				r;
	int				g;
	int				b;

	clr = *(unsigned int *)(tex->addr + (y * tex->ll + x * (tex->bpp / 8)));
	t = ((clr >> 24) & 0xFF);
	r = ((clr >> 16) & 0xFF) * shade;
	g = ((clr >> 8) & 0xFF) * shade;
	b = (clr & 0xFF) * shade;
	return (((t & 0xFF) << 24) + ((r & 0xFF) << 16)
		+ ((g & 0xFF) << 8) + (b & 0xFF));
}

void	texture_error(void *image, char *msg)
{
	image = NULL;
	write(2, msg, 29);
}
