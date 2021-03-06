/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:45:33 by tnanchen          #+#    #+#             */
/*   Updated: 2022/03/24 08:45:54 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/map.h"

void	check_angle(float angle, int *deg)
{
	if (angle < 0)
		angle += PI2;
	if (angle > PI2)
		angle -= PI2;
	*deg = rad_to_deg(angle);
}

float	fix_fisheye(float angle)
{
	if (angle < 0)
		angle += PI2;
	if (angle > PI2)
		angle -= PI2;
	return (cos(angle));
}

void	check_char_map(t_game *game)
{
	if (game->r.char_map != '1')
		game->r.spe = game->r.char_map;
}

void	draw_v_line(t_image *image, t_rays *r, int color)
{
	float	d_x;
	float	d_y;
	int		pix;
	float	p_x;
	float	p_y;

	d_x = 0;
	d_y = r->y2 - r->y1;
	pix = sqrt((d_x * d_x) + (d_y * d_y));
	d_x /= pix;
	d_y /= pix;
	p_x = r->ix;
	p_y = r->y1;
	while (pix)
	{
		my_mlx_pixel_put(image, p_x, p_y, color);
		p_x += d_x;
		p_y += d_y;
		--pix;
	}
}

void	draw_ray(t_image *image, t_map *m, t_rays *r, int color)
{
	float	d_x;
	float	d_y;
	int		pix;
	float	p_x;
	float	p_y;

	d_x = r->x - m->pos_x;
	d_y = r->y - m->pos_y;
	pix = sqrt((d_x * d_x) + (d_y * d_y));
	d_x /= pix;
	d_y /= pix;
	p_x = m->pos_x;
	p_y = m->pos_y;
	while (pix)
	{
		my_mlx_pixel_put(image, p_x, p_y, color);
		p_x += d_x;
		p_y += d_y;
		--pix;
	}
}
