/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:22:06 by tnanchen          #+#    #+#             */
/*   Updated: 2022/03/24 08:46:04 by tnanchen         ###   ########.fr       */
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
