#include "../../includes/cub3d.h"
#include "../../includes/map.h"

/*
	2 = flag ->	but décoratif
	3 = biblio -> porte secrète
	4 = interupteur non-activé (up) placé à côté d'une biblio -> ouvrir la porte secrète d'à côté
	5 = interupteur activé (down) -> plus utilisable, car a déjà ouvert la porte
	9 = espace vide comme 0 mais apparait en gris foncé sur la minimap
*/

t_img  *ray_texture(float ray_a, t_rays *r)
{
	if (r->spe == '2')
		return (&r->tex_flag);
	if (r->spe == '3')
		return (&r->tex_biblio);
	if (r->spe == '4')
		return (&r->tex_iu);
	if (r->spe == '5')
		return (&r->tex_id);
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

void	door_textures_init(t_rays *r, t_game *game)
{
	r->tex_flag.image = mlx_xpm_file_to_image(
		game->mlx, "./textures/flag.xpm", &r->tex_flag.width, &r->tex_flag.heigth);
	if (!r->tex_flag.image)
		texture_error(r->tex_flag.image, "error loading D1_texture_xpm\n");
	else
		r->tex_flag.addr = mlx_get_data_addr(
			r->tex_flag.image, &r->tex_flag.bpp, &r->tex_flag.ll, &r->tex_flag.e);
	r->tex_biblio.image = mlx_xpm_file_to_image(
		game->mlx, "./textures/biblio.xpm", &r->tex_biblio.width, &r->tex_biblio.heigth);
	if (!r->tex_biblio.image)
		texture_error(r->tex_biblio.image, "error loading D2_texture_xpm\n");
	else
		r->tex_biblio.addr = mlx_get_data_addr(
			r->tex_biblio.image, &r->tex_biblio.bpp, &r->tex_biblio.ll, &r->tex_biblio.e);
}

void	interuptor_textures_init(t_rays *r, t_game *game)
{
	r->tex_iu.image = mlx_xpm_file_to_image(
		game->mlx, "./textures/i_up.xpm", &r->tex_iu.width, &r->tex_iu.heigth);
	if (!r->tex_iu.image)
		texture_error(r->tex_iu.image, "error loading IU_texture_xpm\n");
	else
		r->tex_iu.addr = mlx_get_data_addr(
			r->tex_iu.image, &r->tex_iu.bpp, &r->tex_iu.ll, &r->tex_iu.e);
	r->tex_id.image = mlx_xpm_file_to_image(
		game->mlx, "./textures/i_down.xpm", &r->tex_id.width, &r->tex_id.heigth);
	if (!r->tex_id.image)
		texture_error(r->tex_id.image, "error loading ID_texture_xpm\n");
	else
		r->tex_id.addr = mlx_get_data_addr(
			r->tex_id.image, &r->tex_id.bpp, &r->tex_id.ll, &r->tex_id.e);
}
