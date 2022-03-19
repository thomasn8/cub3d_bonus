#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	horizontal_loop(t_map *m, t_rays *r)
{
	while (++r->i < m->rows - 2)
	{
		r->mx = ((int)r->x) / m->m_size;
		r->my = ((int)r->y) / m->m_size;
		if (r->x >= 0 && r->x < m->w && r->y >= 0 && r->y < m->h 
			&& !map_char(m->map[r->my + r->shift][r->mx]))
		{
			r->hx = r->x;
			r->hy = r->y;
			r->dist_h = sqrt(powf((r->x - m->pos_x), 2) + powf((r->y - m->pos_y), 2));
			r->i = m->rows;
			if (m->map[r->my + r->shift][r->mx] == '2')
				r->spe = '2';
		}
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
}

static void	vertical_loop(t_map *m, t_rays *r)
{
	while (++r->i < m->cols - 2)
	{
		r->mx = ((int)r->x) / m->m_size;
		r->my = ((int)r->y) / m->m_size;
		if (r->x >= 0 && r->x < m->w && r->y >= 0 && r->y < m->h
			&& !map_char(m->map[r->my][r->mx + r->shift]))
		{
			r->vx = r->x;
			r->vy = r->y;
			r->dist_v = sqrt(powf((r->x - m->pos_x), 2) + powf((r->y - m->pos_y), 2));
			r->i = m->cols;
			if (m->map[r->my][r->mx + r->shift] == '2')
				r->spe = '2';
		}
		else
		{
			r->x += r->xo;
			r->y += r->yo;
		}
	}
}

void	ray_horizontal_check(t_map *m, t_rays *r)
{
	r->i = -1;
	r->shift = 0;
	if (m->a_deg > 0 && m->a_deg < 180) 							// player regarde en haut
	{
		r->y = ((int)(m->pos_y / m->m_size)) * m->m_size;
		r->x = (m->pos_y - r->y) * r->atan + m->pos_x;
		r->yo = -m->m_size;
		r->xo = -r->yo * r->atan;
		r->shift = -1;
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
	horizontal_loop(m, r);
}

void	ray_vertical_check(t_map *m, t_rays *r)
{
	r->i = -1;
	r->shift = 0;
	if (m->a_deg > 90 && m->a_deg < 270) 							// player regarde à gauche
	{
		r->x = ((int)(m->pos_x / m->m_size)) * m->m_size;
		r->y = (m->pos_x - r->x) * r->ntan + m->pos_y;
		r->xo = -m->m_size;
		r->yo = -r->xo * r->ntan;
		r->shift = -1;
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
	vertical_loop(m, r);
}
