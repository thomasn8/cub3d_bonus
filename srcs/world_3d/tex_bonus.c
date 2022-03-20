#include "../../includes/cub3d.h"
#include "../../includes/map.h"

void	tex_door_create(t_rays *r, t_game *game)
{
	r->tex_biblio.image = mlx_xpm_file_to_image(
		game->mlx, "./textures/biblio.xpm", &r->tex_biblio.width, &r->tex_biblio.heigth);
	if (!r->tex_biblio.image)
		texture_error(r->tex_biblio.image, "error loading DO_texture_xpm\n");
	else
		r->tex_biblio.addr = mlx_get_data_addr(
			r->tex_biblio.image, &r->tex_biblio.bpp, &r->tex_biblio.ll, &r->tex_biblio.e);
}

void	tex_interuptor_create(t_rays *r, t_game *game)
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

void	tex_deco_create(t_rays *r, t_game *game)
{
	r->tex_flag.image = mlx_xpm_file_to_image(
		game->mlx, "./textures/flag.xpm", &r->tex_flag.width, &r->tex_flag.heigth);
	if (!r->tex_flag.image)
		texture_error(r->tex_flag.image, "error loading D1_texture_xpm\n");
	else
		r->tex_flag.addr = mlx_get_data_addr(
			r->tex_flag.image, &r->tex_flag.bpp, &r->tex_flag.ll, &r->tex_flag.e);
	r->tex_steel.image = mlx_xpm_file_to_image(
		game->mlx, "./textures/steel.xpm", &r->tex_steel.width, &r->tex_steel.heigth);
	if (!r->tex_steel.image)
		texture_error(r->tex_steel.image, "error loading D2_texture_xpm\n");
	else
		r->tex_steel.addr = mlx_get_data_addr(
			r->tex_steel.image, &r->tex_steel.bpp, &r->tex_steel.ll, &r->tex_steel.e);
}
