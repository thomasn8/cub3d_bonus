#include "../../includes/cub3d.h"
#include "../../includes/map.h"

// détermine la taille d'un block en pixel dans la minimap
// et centre la minimap dans la barre du bas
int	get_m_size(int cols, int rows)
{
	int max_w;
	int max_h;
	int	m_size1;
	int	m_size2;

	max_w = (WIDTH / 2) - (2 * MARGIN);
	max_h = MENU_HEIGTH - (2 * MARGIN);
	m_size1 = max_w / cols;
	m_size2 = max_h / rows;
	if (m_size1 > m_size2)
		return (m_size2);
	return (m_size1);
}
