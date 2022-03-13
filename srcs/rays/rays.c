#include "../../includes/cub3d.h"
#include "../../includes/map.h"

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

void	draw_3d(t_game *game, t_map *m, t_rays *r)
{
	float		line_h;
	int			lines;
	static int	start_x = 0;
	int			ray_w;
	// float			offset;
	(void) m;

	line_h = game->world_h * m->m_size / r->dist;
	if (line_h > game->world_h)
		line_h = game->world_h;
	lines = -1;
	ray_w = game->width / M_RAYS;
	// offset = game->world_h - (line_h / 2);
	// printf("lineH: %f\n", line_h);
	while (++lines < ray_w)
	{
		draw_line(&game->world, start_x + lines, 0, start_x + lines, game->world_h, M_WALL_COLOR);
		draw_line(&game->world, start_x + lines, 0, start_x + lines, line_h, BLUE);
		// draw_line(&game->world, start_x + lines, offset, start_x + lines, line_h + offset);
	}
	if (r->rays > 1)
		start_x += ray_w;
	else
		start_x = 0;
}

void	cast_rays(t_game *game, t_image *map, t_map *m)
{
	t_rays	r;
	(void) game;
	(void) map;

	m->pos_x += M_HALF_PLAYER;
	m->pos_y += M_HALF_PLAYER;
	m->a_rad += M_HALF_RAYS * M_1_DEG_RAD;
	check_angle(m->a_rad, &m->a_deg);
	r.rays = -1;
	while (++r.rays < M_RAYS)
	{
		init_casting(&r, m->a_rad);
		r.i = -1;
		horizontal_wall_intersection(m, &r);
		r.i = -1;
		vertical_wall_intersection(m, &r);
		compare_dist(&r);
		printf("Ray #%d, distance: %f\n", r.rays, r.dist);
		draw_3d(game, m, &r);
		draw_ray(map, m, &r, RED);				// à enlever plus tard
		m->a_rad -=  M_1_DEG_RAD;
		check_angle(m->a_rad, &m->a_deg);
	}
	// printf("\n");
	m->pos_x -= M_HALF_PLAYER;
	m->pos_y -= M_HALF_PLAYER;
	m->a_rad += M_HALF_RAYS * M_1_DEG_RAD;
	m->a_deg = rad_to_deg(m->a_rad);
	
}
