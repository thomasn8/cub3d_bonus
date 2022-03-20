#include "../../includes/cub3d.h"
#include "../../includes/map.h"
#include "../../includes/event.h"

void	weapon_press(int k, t_game *game)
{
	if (k == K_UP && game->weapon == 1)
		kat_attack(game, 'p');
	else if (k == K_DOWN && game->weapon == 1)
		kat_defense(game, 'p');
	else if (k == K_UP && game->weapon == 2)
		gun_attack(game, 'p');
	else if (k == K_DOWN && game->weapon == 2)
		gun_defense(game, 'p');
}

void	weapon_release(int k, t_game *game)
{
	if (k == K_1)
		game->weapon = 1;
	else if (k == K_2)
		game->weapon = 2;
	else if (k == K_UP && game->weapon == 1)
		kat_attack(game, 'r');
	else if (k == K_DOWN && game->weapon == 1)
		kat_defense(game, 'r');
	else if (k == K_UP && game->weapon == 2)
		gun_attack(game, 'r');
	else if (k == K_DOWN && game->weapon == 2)
		gun_defense(game, 'r');
}

void	weapon_display(t_game *game)
{
// run state
	if (game->state == 0 && game->weapon == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_weapon1_run.image,
			game->m.w_offset + 75, game->world_h - game->tex_weapon1_run.heigth);
	else if (game->state == 0 && game->weapon == 2)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_weapon2_run.image, 
			game->m.w_offset + 75, game->world_h - game->tex_weapon2_run.heigth);
// hit state
	else if (game->state == 1 && game->weapon == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_weapon1_hit.image,
		game->m.w_offset + 75, game->world_h - game->tex_weapon1_hit.heigth);
	else if (game->state == 1 && game->weapon == 2)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_weapon2_hit.image,
		game->m.w_offset + 75, game->world_h - game->tex_weapon2_hit.heigth);
// def state
	else if (game->state == 2 && game->weapon == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_weapon1_def.image,
		game->m.w_offset + 75, game->world_h - game->tex_weapon1_def.heigth);
	else if (game->state == 2 && game->weapon == 2)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_weapon2_def.image,
		game->m.w_offset + 75, game->world_h - game->tex_weapon2_def.heigth);
}
