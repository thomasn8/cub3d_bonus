#include "../../includes/cub3d.h"
#include "../../includes/map.h"

void	draw_lines(t_image *image, t_rays *r, int color)
{
	double	d_x;
	double	d_y;
	int		pix;
	double	p_x;
	double	p_y;

	d_x = r->x2 - r->x1;
	d_y = r->y2 - r->y1;
	pix = sqrt((d_x * d_x) + (d_y * d_y));
	d_x /= pix;
	d_y /= pix;
	p_x = r->x1;
	p_y = r->y1;
	while (pix)
	{
		my_mlx_pixel_put(image, p_x, p_y, color);
		p_x += d_x;
		p_y += d_y;
		--pix;
	}
}

void	check_angle(float angle, int *deg)
{
	if (angle < 0)
		angle += PI2;
	if (angle > PI2)
		angle -= PI2;
	*deg = rad_to_deg(angle);
}

char	compare_dist(t_rays	*r)
{
	if (r->dist_v != 0 && (r->dist_h == 0 || r->dist_v < r->dist_h))
	{
		r->x = r->vx;
		r->y = r->vy;
		r->dist = r->dist_v;
		return ('v');
	}
	r->x = r->hx;
	r->y = r->hy;
	r->dist = r->dist_h;
	return ('h');
}

float fix_fisheye(float angle)
{ 
	if (angle < 0)
		angle += PI2;
	if (angle > PI2)
		angle -= PI2;
	return (cos(angle));
}

void	draw_ray(t_image *image, t_map *m, t_rays *r, int color)
{
	float	delta_x;
	float	delta_y;
	int		pixels;
	float	pixel_x;
	float	pixel_y;

	delta_x = r->x - m->pos_x;
	delta_y = r->y - m->pos_y;
	pixels = sqrt((delta_x * delta_x) + (delta_y * delta_y));
	delta_x /= pixels;
	delta_y /= pixels;
	pixel_x = m->pos_x;
	pixel_y = m->pos_y;
	while (pixels)
	{
		my_mlx_pixel_put(image, pixel_x, pixel_y, color);
		pixel_x += delta_x;
		pixel_y += delta_y;
		--pixels;
	}
}
