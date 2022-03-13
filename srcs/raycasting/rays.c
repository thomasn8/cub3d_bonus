#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static float distance(t_map *m, t_rays *r)
{
	float dist;

	dist = cos(deg_to_rad(m->a_rad)) * (r->x - m->pos_x)
		- sin(deg_to_rad(m->a_rad)) * (r->y - m->pos_y);
	if (dist < 0)
		dist *= -1;
	return (dist);
}

static void	horizontal_loop(t_map *m, t_rays *r, int offset)
{
	while (++r->i < m->rows - 2)
	{
		r->mx = ((int)r->x) / m->m_size;
		r->my = ((int)r->y) / m->m_size;
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
		r->mx = ((int)r->x) / m->m_size;
		r->my = ((int)r->y) / m->m_size;
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
		r->y = ((int)(m->pos_y / m->m_size)) * m->m_size;
		r->x = (m->pos_y - r->y) * r->atan + m->pos_x;
		r->yo = -m->m_size;
		r->xo = -r->yo * r->atan;
		offset = -1;
	}
	else if (m->a_deg > 180) 										// player regarde en bas
	{
		r->y = ((int)(m->pos_y / m->m_size)) * m->m_size + m->m_size;
		r->x = (m->pos_y - r->y) * r->atan + m->pos_x;
		r->yo = m->m_size;
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
		r->x = ((int)(m->pos_x / m->m_size)) * m->m_size;
		r->y = (m->pos_x - r->x) * r->ntan + m->pos_y;
		r->xo = -m->m_size;
		r->yo = -r->xo * r->ntan;
		offset = -1;
	}
	else if (m->a_deg < 90 || m->a_deg > 270) 						// player regarde à droite
	{
		r->x = ((int)(m->pos_x / m->m_size)) * m->m_size + m->m_size;
		r->y = (m->pos_x - r->x) * r->ntan + m->pos_y;
		r->xo = m->m_size;
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
