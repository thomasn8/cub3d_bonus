#include "../../includes/cub3d.h"
#include "../../includes/map.h"
#include "../../includes/event.h"

void	draw_viewfinder(t_game *game)
{
	game->p.i = 3;
	while (game->p.i--)
	{
		game->p.o = 0;
		if (game->p.i == 1)
			game->p.o = 5;
		game->p.x1 = game->width / 2 - 5 - game->p.o;
		game->p.x2 = game->width / 2 + 5 + game->p.o;
		game->p.y1 = game->world_h / 2 - 1 + game->p.i;
		game->p.y2 = game->world_h / 2 - 1 + game->p.i;
		draw_line(game, &game->world, &game->p, YELLOW);
	}
	game->p.i = 3;
	while (game->p.i--)
	{
		game->p.o = 0;
		if (game->p.i == 1)
			game->p.o = 5;
		game->p.y1 = game->world_h / 2 - 5 - game->p.o;
		game->p.y2 = game->world_h / 2 + 5 + game->p.o;
		game->p.x1 = game->width / 2 - 1 + game->p.i;
		game->p.x2 = game->width / 2 - 1 + game->p.i;
		draw_line(game, &game->world, &game->p, YELLOW);
	}
}

void	weapon_press(int k, t_game *game)
{
	if (k == K_UP && game->weapon == 1)
		kat_attack(game, 'p');
	else if (k == K_DOWN && game->weapon == 1)
		kat_defense(game, 'p');
	else if (k == K_UP && game->weapon == 2)
		gun_shoot(game, 'p');
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
		gun_shoot(game, 'r');
}

// weapon katana :	state 0 = run	|	state 1 = hit		|	state 2 = defense
// weapon gun :		state 0 = run	|	state 1 = chargé	|	state 2 = lancé
void	weapon_display(t_game *game)
{
	if (game->weapon == 1 && game->state == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_kat_run.image,
			game->m.w_offset + 75, game->world_h - game->tex_kat_run.heigth);
	else if (game->weapon == 1 && game->state == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_kat_hit.image,
		game->m.w_offset + 75, game->world_h - game->tex_kat_hit.heigth);
	else if (game->weapon == 1 && game->state == 2)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_kat_def.image,
		game->m.w_offset - 175, game->world_h - game->tex_kat_def.heigth);
	
	else if (game->weapon == 2 && game->state == 0)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_gun_run.image, 
			game->m.w_offset + 75, game->world_h - game->tex_gun_run.heigth);
	else if (game->weapon == 2 && game->state == 1)
		mlx_put_image_to_window(game->mlx, game->win, game->tex_gun_run.image,
		game->m.w_offset + 75, game->world_h - game->tex_gun_run.heigth - 100);
	// else if (game->weapon == 2 && game->state == 2)
	// 	mlx_put_image_to_window(game->mlx, game->win, game->tex_gun_3.image,
	// 	game->m.w_offset + 88, game->world_h - game->tex_gun_3.heigth - 260);
}
