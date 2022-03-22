/* 
!!! Adapter le nombres de textures correspondant à des murs ... !!!
	- ... soit dans map.h le define de W_TEX
	- ... soit dans map.c, dans color() + dans moves.c, dans map_char()

- Deco
	2 = flag ->	but décoratif
	6 = steel -> but décoratif

- Interactions portes
	3 = biblio -> porte secrète
	4 = interupteur non-activé (rouge-up) placé à côté d'une biblio -> ouvrir la porte secrète d'à côté
	5 = interupteur activé (vert-down) placé à côté d'une biblio -> fermet la porte précédement ouverte
	9 = porte ouverte devenu un espace vide (mur -> espace). Apparait en gris foncé sur la minimap

- Ennemies
	8 = enemy

- Non-attribués
	7 ;

*/

#include "../../includes/cub3d.h"
#include "../../includes/map.h"

t_img  *ray_texture(float ray_a, t_rays *r)
{
	if (r->spe == '2')
		return (&r->tex_flag);
	else if (r->spe == '3')
		return (&r->tex_biblio);
	else if (r->spe == '4')
		return (&r->tex_iu);
	else if (r->spe == '5')
		return (&r->tex_id);
	else if (r->spe == '6')
		return (&r->tex_steel);
	if (r->cross == 'v')											// faces W et E
	{
		if (ray_a > 90 && ray_a < 270 && r->tex_w.image)			// W
			return (&r->tex_w);
		else if ((ray_a < 90 || ray_a > 270) && r->tex_e.image)		// E
			return (&r->tex_e);
	}
	else if (r->cross == 'h')										// sinon faces N et S
	{
		if (ray_a > 0 && ray_a < 180 && r->tex_n.image)				// N
			return (&r->tex_n);
		else if (ray_a > 180 && r->tex_s.image)						// S
			return (&r->tex_s);
	}
	return (NULL);
}

int	ray_color(float ray_a, t_rays *r)
{
	if (r->cross == 'v')					// faces W et E
	{
		if (ray_a > 90 && ray_a < 270)		// W
			return (DEF1);
		else								// E
			return (DEF2);
	}
	else if (r->cross == 'h')				// faces N et S
	{
		if (ray_a > 0 && ray_a < 180)		// N
			return (DEF3);
		else								// S
			return (DEF4);
	}
	return (WHITE);
}

float	color_shade(float ray_a, t_rays *r)
{
	if (r->cross == 'v')					// faces W et E
	{
		if (ray_a > 90 && ray_a < 270)		// W
			return (0.5);
		else								// E
			return (1);
	}
	else if (r->cross == 'h')				// faces N et S
	{
		if (ray_a > 0 && ray_a < 180)		// N
			return (0.8);
		else								// S
			return (0.6);
	}
	return (1);
}

void	v_textures_init(t_rays *r, t_game *game)
{
	r->tex_n.image = mlx_xpm_file_to_image(
			game->mlx, game->m.no, &r->tex_n.width, &r->tex_n.heigth);
	if (!r->tex_n.image)
		texture_error(r->tex_n.image, "error loading NO_texture_xpm\n");
	else
		r->tex_n.addr = mlx_get_data_addr(
				r->tex_n.image, &r->tex_n.bpp, &r->tex_n.ll, &r->tex_n.e);
	r->tex_s.image = mlx_xpm_file_to_image(
			game->mlx, game->m.so, &r->tex_s.width, &r->tex_s.heigth);
	if (!r->tex_s.image)
		texture_error(r->tex_s.image, "error loading SO_texture_xpm\n");
	else
		r->tex_s.addr = mlx_get_data_addr(
				r->tex_s.image, &r->tex_s.bpp, &r->tex_s.ll, &r->tex_s.e);
}

void	h_textures_init(t_rays *r, t_game *game)
{
	r->tex_e.image = mlx_xpm_file_to_image(
			game->mlx, game->m.ea, &r->tex_e.width, &r->tex_e.heigth);
	if (!r->tex_e.image)
		texture_error(r->tex_e.image, "error loading EA_texture_xpm\n");
	else
		r->tex_e.addr = mlx_get_data_addr(
				r->tex_e.image, &r->tex_e.bpp, &r->tex_e.ll, &r->tex_e.e);
	r->tex_w.image = mlx_xpm_file_to_image(
			game->mlx, game->m.we, &r->tex_w.width, &r->tex_w.heigth);
	if (!r->tex_w.image)
		texture_error(r->tex_w.image, "error loading WE_texture_xpm\n");
	else
		r->tex_w.addr = mlx_get_data_addr(
				r->tex_w.image, &r->tex_w.bpp, &r->tex_w.ll, &r->tex_w.e);
}
