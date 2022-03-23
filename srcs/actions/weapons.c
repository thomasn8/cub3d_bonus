/*
	POUR L'INSTANT UNIQUEMENT ANIMATION VISUELLE MAIS N'ENREGISTRE PAS LE HIT OU LE DEF
	à programmer, prendre interaction.c comme modèle pour gérer le point d'impact
*/

#include "../../includes/cub3d.h"
#include "../../includes/map.h"

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
	if (k == 'p' && game->state == 0)			// run : shuriken en bas
		game->state = 1;						// press : shuriken en haut, chargé
	else if (k == 'r' && game->state == 1)		// released : shuriken lancé, vrille vers cible
		game->state = 2;
	if (k == 'r' && game->state == 2)		
		game->state = 0;						// run : shuriken en bas
}
