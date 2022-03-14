#include "../../includes/cub3d.h"
#include "../../includes/map.h"

float deg_to_rad(int angle)
{
	return (angle * PI / 180);
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
	*deg = rad_to_deg(angle);
}

void	compare_dist(t_rays	*r)
{
	if (r->dist_v != 0 && (r->dist_h == 0 || r->dist_v < r->dist_h))
	{
		r->x = r->vx;
		r->y = r->vy;
		r->dist = r->dist_v;
		r->cross = 'v';
	}
	else if (r->dist_h != 0 && (r->dist_v == 0 || r->dist_h < r->dist_v))
	{
		r->x = r->hx;
		r->y = r->hy;
		r->dist = r->dist_h;
		r->cross = 'h';
	}
}

float fix_fisheye(float angle)
{ 
	if (angle < 0)
		angle += PI2;
	if (angle > PI2)
		angle -= PI2;
	return (cos(angle));
}
