#include "../../includes/cub3d.h"

static void	weapons_error(char *msg)
{
	write(2, msg, 29);
	exit(1);
}

void	tex_kat_create(t_game *game)
{
	game->tex_kat_run.image = mlx_xpm_file_to_image(
		game->mlx, "./weapons/kat_run", &game->tex_kat_run.width, &game->tex_kat_run.heigth);
	if (!game->tex_kat_run.image)
		weapons_error("error loading K0_texture_xpm\n");
	else
		game->tex_kat_run.addr = mlx_get_data_addr(
			game->tex_kat_run.image, &game->tex_kat_run.bpp, &game->tex_kat_run.ll, &game->tex_kat_run.e);
	
	game->tex_kat_hit.image = mlx_xpm_file_to_image(
		game->mlx, "./weapons/kat_hit", &game->tex_kat_hit.width, &game->tex_kat_hit.heigth);
	if (!game->tex_kat_hit.image)
		weapons_error("error loading K1_texture_xpm\n");
	else
		game->tex_kat_hit.addr = mlx_get_data_addr(
			game->tex_kat_hit.image, &game->tex_kat_hit.bpp, &game->tex_kat_hit.ll, &game->tex_kat_hit.e);
	
	game->tex_kat_def.image = mlx_xpm_file_to_image(
		game->mlx, "./weapons/kat_def", &game->tex_kat_def.width, &game->tex_kat_def.heigth);
	if (!game->tex_kat_def.image)
		weapons_error("error loading K2_texture_xpm\n");
	else
		game->tex_kat_def.addr = mlx_get_data_addr(
			game->tex_kat_def.image, &game->tex_kat_def.bpp, &game->tex_kat_def.ll, &game->tex_kat_def.e);
}

void	tex_gun_create(t_game *game)
{
	game->tex_gun_run.image = mlx_xpm_file_to_image(
		game->mlx, "./weapons/gun_run", &game->tex_gun_run.width, &game->tex_gun_run.heigth);
	if (!game->tex_gun_run.image)
		weapons_error("error loading G0_texture_xpm\n");
	else
		game->tex_gun_run.addr = mlx_get_data_addr(
			game->tex_gun_run.image, &game->tex_gun_run.bpp, &game->tex_gun_run.ll, &game->tex_gun_run.e);
	
	game->tex_gun_hit.image = mlx_xpm_file_to_image(
		game->mlx, "./weapons/gun_hit", &game->tex_gun_hit.width, &game->tex_gun_hit.heigth);
	if (!game->tex_gun_hit.image)
		weapons_error("error loading G1_texture_xpm\n");
	else
		game->tex_gun_hit.addr = mlx_get_data_addr(
			game->tex_gun_hit.image, &game->tex_gun_hit.bpp, &game->tex_gun_hit.ll, &game->tex_gun_hit.e);
	
	game->tex_gun_def.image = mlx_xpm_file_to_image(
		game->mlx, "./weapons/gun_def", &game->tex_gun_def.width, &game->tex_gun_def.heigth);
	if (!game->tex_gun_def.image)
		weapons_error("error loading G2_texture_xpm\n");
	else
		game->tex_gun_def.addr = mlx_get_data_addr(
			game->tex_gun_def.image, &game->tex_gun_def.bpp, &game->tex_gun_def.ll, &game->tex_gun_def.e);
}
