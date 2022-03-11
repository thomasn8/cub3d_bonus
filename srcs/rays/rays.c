#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	horizontal_loop(t_map *m, t_rays *r, int offset)
{
	while (++r->i < m->rows - 2)
	{
		r->mx = ((int)r->x) / M_SIZE;
		r->my = ((int)r->y) / M_SIZE;
		if(r->x >= 0 && r->x < m->w && r->y >= 0 && r->y < m->h 
			&& m->map[r->my + offset][r->mx] == '1')
		{
			r->hx = r->x;
			r->hy = r->y;
			r->dist_h = distance(m, r);
			r->i = m->rows;
		}
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
}

static void	vertical_loop(t_map *m, t_rays *r, int offset)
{
	while (++r->i < m->cols - 2)
	{
		r->mx = ((int)r->x) / M_SIZE;
		r->my = ((int)r->y) / M_SIZE;
		if(r->x >= 0 && r->x < m->w && r->y >= 0 && r->y < m->h
			&& m->map[r->my][r->mx + offset] == '1')
		{
			r->vx = r->x;
			r->vy = r->y;
			r->dist_v = distance(m, r);
			r->i = m->cols;
		}
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
}

void	horizontal_wall_intersection(t_map *m, t_rays *r)
{
	int	offset;

	offset = 0;
	if (m->a_deg > 0 && m->a_deg < 180) 							// player regarde en haut
	{
		r->y = ((int)(m->pos_y / M_SIZE)) * M_SIZE;
		r->x = (m->pos_y - r->y) * r->atan + m->pos_x;
		r->yo = -M_SIZE;
		r->xo = -r->yo * r->atan;
		offset = -1;
	}
	else if (m->a_deg > 180) 										// player regarde en bas
	{
		r->y = ((int)(m->pos_y / M_SIZE)) * M_SIZE + M_SIZE;
		r->x = (m->pos_y - r->y) * r->atan + m->pos_x;
		r->yo = M_SIZE;
		r->xo = -r->yo * r->atan;
	}
	else															// player regarde en horizontal
	{
		r->y = m->pos_y;
		r->x = m->pos_x;
		r->i = m->rows;
	}
	horizontal_loop(m, r, offset);
}

void	vertical_wall_intersection(t_map *m, t_rays *r)
{
	int	offset;

	offset = 0;
	if (m->a_deg > 90 && m->a_deg < 270) 							// player regarde à gauche
	{
		r->x = ((int)(m->pos_x / M_SIZE)) * M_SIZE;
		r->y = (m->pos_x - r->x) * r->ntan + m->pos_y;
		r->xo = -M_SIZE;
		r->yo = -r->xo * r->ntan;
		offset = -1;
	}
	else if (m->a_deg < 90 || m->a_deg > 270) 						// player regarde à droite
	{
		r->x = ((int)(m->pos_x / M_SIZE)) * M_SIZE + M_SIZE;
		r->y = (m->pos_x - r->x) * r->ntan + m->pos_y;
		r->xo = M_SIZE;
		r->yo = -r->xo * r->ntan;
	}
	else															// player regarde en vertical
	{
		r->y = m->pos_y;
		r->x = m->pos_x;
		r->i = m->cols;
	}
	vertical_loop(m, r, offset);
}

void	cast_rays(t_image *map, t_map *m)
{
	t_rays	r;

	m->pos_x += M_HALF_PLAYER;
	m->pos_y += M_HALF_PLAYER;
	m->a_rad -= M_HALF_RAYS * M_1_DEG_RAD;
	check_angle(m->a_rad, &m->a_deg);
	r.rays = M_RAYS + 1;
	while (--r.rays)
	{
		init_casting(&r, m->a_rad);
		r.i = -1;
		horizontal_wall_intersection(m, &r);
		r.i = -1;
		vertical_wall_intersection(m, &r);
		compare_dist(&r);
		// printf("Ray #%d, distance: %f\n", r.rays, r.dist);
		draw_ray(map, m, &r, RED);				// à enlever plus tard
		m->a_rad +=  M_1_DEG_RAD;
		check_angle(m->a_rad, &m->a_deg);
	}
	// printf("\n");
	m->pos_x -= M_HALF_PLAYER;
	m->pos_y -= M_HALF_PLAYER;
	m->a_rad -= M_HALF_RAYS * M_1_DEG_RAD;
	m->a_deg = rad_to_deg(m->a_rad);
}
