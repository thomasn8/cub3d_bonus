/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:22:06 by tnanchen          #+#    #+#             */
/*   Updated: 2022/03/24 20:33:25 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"
#include "../../includes/map.h"

/*
	POUR L'INSTANT UNIQUEMENT ANIMATION VISUELLE
	N'ENREGISTRE PAS LE HIT OU LE DEF
	à programmer, prendre interaction.c comme modèle 
	pour gérer le point d'impact
*/

void	kat_defense(t_game *game, char k)
{
	if (k == 'p')
		game->state = 2;
	else if (k == 'r')
		game->state = 0;
}

void	kat_attack(t_game *game, char k)
{
	if (k == 'p')
		game->state = 1;
	else if (k == 'r')
		game->state = 0;
}

void	gun_shoot(t_game *game, char k)
{
	if (k == 'p' && game->state == 0)
		game->state = 1;
	else if (k == 'r' && game->state == 1)
		game->state = 2;
	if (k == 'r' && game->state == 2)
		game->state = 0;
}

void	weapons_dimensions(t_game *game)
{
	game->kat_run_mw = game->margin_w + game->m.w_offset + 75;
	game->kat_run_mh = game->margin_h + game->world_h
		- game->tex_kat_run.heigth;
	game->kat_hit_mw = game->margin_w + game->m.w_offset + 75;
	game->kat_hit_mh = game->margin_h + game->world_h
		- game->tex_kat_hit.heigth;
	game->kat_def_mw = game->margin_w + game->m.w_offset - 175;
	game->kat_def_mh = game->margin_h + game->world_h
		- game->tex_kat_def.heigth;
	game->gun_run_mw = game->margin_w + game->m.w_offset + 75;
	game->gun_run_mh = game->margin_h + game->world_h
		- game->tex_gun_run.heigth;
	game->gun_shoot_mw = game->margin_w + game->m.w_offset + 75;
	game->gun_shoot_mh = game->margin_h + game->world_h
		- game->tex_gun_run.heigth - 100;
}
