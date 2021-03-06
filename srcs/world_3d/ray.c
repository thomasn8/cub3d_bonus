/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:55:47 by tnanchen          #+#    #+#             */
/*   Updated: 2022/03/24 08:04:05 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	horizontal_loop(t_map *m, t_rays *r)
{
	while (++r->i < m->rows - 2)
	{
		r->hmx = ((int)r->x) / m->m_size;
		r->hmy = ((int)r->y) / m->m_size;
		if (r->x >= 0 && r->x < m->w && r->y >= 0 && r->y < m->h
			&& !map_char(m->map[r->hmy + r->h_shift][r->hmx]))
		{
			r->hx = r->x;
			r->hy = r->y;
			r->dist_h = sqrt(powf((r->x - m->pos_x), 2)
					+ powf((r->y - m->pos_y), 2));
			r->i = m->rows;
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
		r->vmx = ((int)r->x) / m->m_size;
		r->vmy = ((int)r->y) / m->m_size;
		if (r->x >= 0 && r->x < m->w && r->y >= 0 && r->y < m->h
			&& !map_char(m->map[r->vmy][r->vmx + r->v_shift]))
		{
			r->vx = r->x;
			r->vy = r->y;
			r->dist_v = sqrt(powf((r->x - m->pos_x), 2)
					+ powf((r->y - m->pos_y), 2));
			r->i = m->cols;
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
	r->h_shift = 0;
	if (m->a_deg > 0 && m->a_deg < 180)
	{
		r->y = ((int)(m->pos_y / m->m_size)) * m->m_size;
		r->x = (m->pos_y - r->y) * r->atan + m->pos_x;
		r->yo = -m->m_size;
		r->xo = -r->yo * r->atan;
		r->h_shift = -1;
	}
	else if (m->a_deg > 180)
	{
		r->y = ((int)(m->pos_y / m->m_size)) * m->m_size + m->m_size;
		r->x = (m->pos_y - r->y) * r->atan + m->pos_x;
		r->yo = m->m_size;
		r->xo = -r->yo * r->atan;
	}
	else
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
	r->v_shift = 0;
	if (m->a_deg > 90 && m->a_deg < 270)
	{
		r->x = ((int)(m->pos_x / m->m_size)) * m->m_size;
		r->y = (m->pos_x - r->x) * r->ntan + m->pos_y;
		r->xo = -m->m_size;
		r->yo = -r->xo * r->ntan;
		r->v_shift = -1;
	}
	else if (m->a_deg < 90 || m->a_deg > 270)
	{
		r->x = ((int)(m->pos_x / m->m_size)) * m->m_size + m->m_size;
		r->y = (m->pos_x - r->x) * r->ntan + m->pos_y;
		r->xo = m->m_size;
		r->yo = -r->xo * r->ntan;
	}
	else
	{
		r->y = m->pos_y;
		r->x = m->pos_x;
		r->i = m->cols;
	}
	vertical_loop(m, r);
}

void	compare_rays(t_game *game)
{
	if (game->r.dist_v != 0
		&& (game->r.dist_h == 0 || game->r.dist_v < game->r.dist_h))
	{
		game->r.x = game->r.vx;
		game->r.y = game->r.vy;
		game->r.wx = game->r.x / game->m.m_size;
		game->r.wy = game->r.y / game->m.m_size;
		game->r.dist = game->r.dist_v;
		game->r.cross = 'v';
		game->r.char_map
			= game->m.map[game->r.vmy][game->r.vmx + game->r.v_shift];
		check_char_map(game);
	}
	else
	{
		game->r.x = game->r.hx;
		game->r.y = game->r.hy;
		game->r.wx = game->r.x / game->m.m_size;
		game->r.wy = game->r.y / game->m.m_size;
		game->r.dist = game->r.dist_h;
		game->r.cross = 'h';
		game->r.char_map
			= game->m.map[game->r.hmy + game->r.h_shift][game->r.hmx];
		check_char_map(game);
	}
}
