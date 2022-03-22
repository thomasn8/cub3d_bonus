#include "../includes/cub3d.h"
#include "../includes/map.h"


float deg_to_rad(int angle)
{
	return (angle * PI / 180);
}

int rad_to_deg(float angle)
{
	return (angle / PI * 180);
}

unsigned int get_color_value(t_image *image, int x, int y)
{
	char *ptr;

	ptr = image->addr + (y * image->line_length + x * (image->bits_per_pixel / 8));
	return (*(unsigned int*)ptr);
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

unsigned int get_tex_color(t_img *tex, int x, int y, float shade)
{
	unsigned int	clr;
	int t;
	int	r;
	int	g;
	int	b;

	clr = *(unsigned int*)(tex->addr + (y * tex->ll + x * (tex->bpp / 8)));
	// return (clr);
	t = ((clr >> 24) & 0xFF);
	r = ((clr >> 16) & 0xFF) * shade;
	g = ((clr >> 8)  & 0xFF) * shade;
	b = (clr         & 0xFF) * shade;
	return (((t & 0xFF) << 24) + ((r & 0xFF) << 16) +
		((g & 0xFF) << 8) + (b & 0xFF));
}

void	texture_error(void *image, char *msg)
{
	image = NULL;
	write(2, msg, 29);
}
