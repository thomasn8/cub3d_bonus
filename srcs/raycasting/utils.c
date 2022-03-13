#include "../../includes/cub3d.h"
#include "../../includes/map.h"

float deg_to_rad(int angle)
{
	return (angle * PI / 180.0);
}

int rad_to_deg(float angle)
{
	return (angle / PI * 180);
}

void	check_angle(float angle, int *deg)
{
	if (angle < 0)
		angle += PI2;
	if (angle > PI2)
		angle -= PI2;
	*deg= rad_to_deg(angle);
}

void	compare_dist(t_rays	*r)
{
	// printf("R#%d: dist_v= %f |vs| dist_h= %f\n", r->rays, r->dist_v, r->dist_h);
	if (r->dist_v != 0 && (r->dist_h == 0 || r->dist_v < r->dist_h))
	{
		r->x = r->vx;
		r->y = r->vy;
		r->dist = r->dist_v;
	}
	else if (r->dist_h != 0 && (r->dist_v == 0 || r->dist_h < r->dist_v))
	{
		r->x = r->hx;
		r->y = r->hy;
		r->dist = r->dist_h;
	}
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
