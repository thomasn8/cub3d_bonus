#include "../../includes/cub3d.h"
#include "../../includes/map.h"

t_img  *ray_texture(float ray_a, t_rays *r)
{
	if (r->cross == 'v')										// faces W et E
	{
		if (ray_a > 90 && ray_a < 270 && r->tex_w.image)		// W
			return (&r->tex_w);
		else if ((ray_a < 90 || ray_a > 270) && r->tex_e.image)	// E
			return (&r->tex_e);
	}															// sinon faces N et S
	if (ray_a > 0 && ray_a < 180 && r->tex_n.image)				// N
		return (&r->tex_n);
	else if (ray_a > 180 && r->tex_s.image)						// S
		return (&r->tex_s);
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
	}										// faces N et S
	if (ray_a > 0 && ray_a < 180)			// N
		return (CH1);
	else									// S
		return (CH2);
	return (0);
}

void	v_textures_init(t_rays *r, t_game *game)
{
	r->tex_n.image = mlx_xpm_file_to_image(
		game->mlx, game->m.no, &r->tex_n.width, &r->tex_n.heigth);
	if (!r->tex_n.image)
	{
		r->tex_n.image = NULL;
		write(2, "Error: loading NO_texture_xpm\n", 29);
	}
	else
		r->tex_n.addr = mlx_get_data_addr(
			r->tex_n.image, &r->tex_n.bpp, &r->tex_n.ll, &r->tex_n.e);
	r->tex_s.image = mlx_xpm_file_to_image(
		game->mlx, game->m.so, &r->tex_s.width, &r->tex_s.heigth);
	if (!r->tex_s.image)
	{
		r->tex_s.image = NULL;
		write(2, "Error: loading SO_texture_xpm\n", 29);
	}
	else
		r->tex_s.addr = mlx_get_data_addr(
			r->tex_s.image, &r->tex_s.bpp, &r->tex_s.ll, &r->tex_s.e);
}

void	h_textures_init(t_rays *r, t_game *game)
{
	r->tex_e.image = mlx_xpm_file_to_image(
		game->mlx, game->m.ea, &r->tex_e.width, &r->tex_e.heigth);
	if (!r->tex_e.image)
	{
		r->tex_e.image = NULL;
		write(2, "Error: loading EA_texture_xpm\n", 29);
	}
	else
		r->tex_e.addr = mlx_get_data_addr(
			r->tex_e.image, &r->tex_e.bpp, &r->tex_e.ll, &r->tex_e.e);
	r->tex_w.image = mlx_xpm_file_to_image(
		game->mlx, game->m.we, &r->tex_w.width, &r->tex_w.heigth);
	if (!r->tex_w.image)
	{
		r->tex_w.image = NULL;
		write(2, "Error: loading WE_texture_xpm\n", 29);
	}
	else
		r->tex_w.addr = mlx_get_data_addr(
			r->tex_w.image, &r->tex_w.bpp, &r->tex_w.ll, &r->tex_w.e);
}
