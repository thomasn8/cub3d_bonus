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

// retourne un int (valeur decimal !) = la couleur de l'image en pos. (x,y)
unsigned int get_color_value(t_image *image, int x, int y)
{
	char *ptr;

	ptr = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	return (*(unsigned int*)ptr);
}

unsigned int get_tex_color(t_img *tex, int x, int y)
{
	char *ptr;

	ptr = tex->addr + (y * tex->line_length + x * (tex->bits_per_pixel / 8));
	return (*(unsigned int*)ptr);
}
