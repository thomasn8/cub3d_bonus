#include "../../includes/cub3d.h"
#include "../../includes/map.h"

float deg_to_rad(int angle)
{
	return (angle * PI / 180);
}

int rad_to_deg(float angle)
{
	return (angle / PI * 180);
}

// retourne la valeur la couleur en un int (valeur decimal !)
unsigned int get_color_value(t_image *image, int x, int y)
{
	char *ptr;

	ptr = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	return (*(unsigned int*)ptr);
}
