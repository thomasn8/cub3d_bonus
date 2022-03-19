#include "../../includes/cub3d.h"
#include "../../includes/map.h"

t_img  *ray_texture(float ray_a, t_rays *r)
{
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
			return (CV1);
		else								// E
			return (CV2);
	}
	else if (r->cross == 'h')				// faces N et S
	{
		if (ray_a > 0 && ray_a < 180)		// N
			return (CH1);
		else								// S
			return (CH2);
	}
	return (0);
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

void	bonus_textures_init(t_rays *r, t_game *game)
{
	r->tex_door.image = mlx_xpm_file_to_image(
		game->mlx, "./textures/door.xpm", &r->tex_door.width, &r->tex_door.heigth);
	if (!r->tex_door.image)
		texture_error(r->tex_door.image, "error loading DO_texture_xpm\n");
	else
		r->tex_door.addr = mlx_get_data_addr(
			r->tex_door.image, &r->tex_door.bpp, &r->tex_door.ll, &r->tex_door.e);
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
