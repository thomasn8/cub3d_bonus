#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	draw_v_line(t_image *image, t_rays *r, int color)
{
	double	d_x;
	double	d_y;
	int		pix;
	double	p_x;
	double	p_y;

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

// FONCTION POUR METTRE LES TEXTURES SUR LES MURS				<-------
static void	walls_texture(float ray_a, t_rays *r)
{
	if (r->cross == 'v')					// faces W et E
	{
		if (ray_a > 90 && ray_a < 270)		// W
			r->color = CV1;
		else								// E
			r->color = CV2;
	}
	else									// faces N et S
	{
		if (ray_a > 0 && ray_a < 180)		// N
			r->color = CH1;
		else								// S
			r->color = CH2;
	}
}

static void	ray_transfo(t_game *game, t_rays *r)
{
	r->dist *= fix_fisheye(game->m.player_angle - game->m.a_rad);
	r->w_bot = game->world_h * game->m.m_size / r->dist;
	if (r->w_bot > game->world_h)
		r->w_bot = game->world_h;
	r->w_top = (game->world_h / 2) - (r->w_bot / 2);
	r->lpr_cpy = game->width / M_2RAYS + 1;
	walls_texture(game->m.a_deg, r);
}

// lpr = ligne par rayon | ix = x pos. sur l'image 3d | iy = y décalage de pos. sur l'image 3d
// w_top = wall top = plafond | w_bot = wall bottom = sol
// ou aussi
// w_top = offset pour le début du mur | w_bot = hauteur du mur
static void	draw_3d(t_game *game, t_rays *r)
{
	ray_transfo(game, r);
	r->lpr = r->lpr_cpy;
	while (--r->lpr)
	{
		r->y1 = 0;
		r->y2 = r->w_top;
		draw_v_line(&game->world, r, game->m.c_ceil);	// plafond
		
		// //// POUR APPLIQUER LA TEXTURE NORD À TOUTES LES FACES :
		// ptr sur l'image de la texture stocké dans r->tex_n.image
		r->iy = -1;
		while (++r->iy < r->w_bot)						// walls
		{
			// r->ty = ...;																// déterminer quel pos.y utiliser dans la tex
			// r->tx = ...;																// déterminer quel pos.x utiliser dans la tex
			// r->tc = get_color_value(r->tex_n.image, r->tx, r->ty);					// choper la couleur de la tex à la bonne position
			my_mlx_pixel_put(&game->world, r->ix, r->iy + r->w_top, r->color);			// utiliser r->tc à la place de r->color
		}
		////////////////////////////////////////////////////////

		r->y1 =  r->w_bot + r->w_top;
		r->y2 = game->world_h;
		draw_v_line(&game->world, r, game->m.c_floor);	// sol
		r->ix++;
	}
}

// utiliser M_05_DEG_RAD pour projeter 120 rayons
// utiliser M_1_DEG_RAD pour projet 60 rayons
// sans oublier d'adapter les M_HALF_RAYS / M_RAYS / M_2RAYS
void	raycasting(t_game *game)
{
	game->m.pos_x += M_HALF_PLAYER;
	game->m.pos_y += M_HALF_PLAYER;
	game->m.player_angle = game->m.a_rad;
	game->m.a_rad += M_RAYS * M_05_DEG_RAD;
	check_angle(game->m.a_rad, &game->m.a_deg);
	game->r.rays = -1;
	game->r.ix = 0;
	while (++game->r.rays < M_2RAYS)
	{
		game->r.dist_v = 0;
		game->r.dist_h = 0;
		game->r.atan = -1 / tan(-game->m.a_rad);
		game->r.ntan = -tan(-game->m.a_rad);
		ray_horizontal_check(&game->m, &game->r);
		ray_vertical_check(&game->m, &game->r);
		compare_dist(&game->r);
		draw_3d(game, &game->r);
		// draw_ray(&game->map, &game->m, &r, RED);						// à enlever plus tard
		game->m.a_rad -=  M_05_DEG_RAD;
		check_angle(game->m.a_rad, &game->m.a_deg);
	}
	game->m.pos_x -= M_HALF_PLAYER;
	game->m.pos_y -= M_HALF_PLAYER;
	game->m.a_rad += M_RAYS * M_05_DEG_RAD;
	game->m.a_deg = rad_to_deg(game->m.a_rad);
}
