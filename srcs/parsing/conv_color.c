#include "../../includes/cub3d.h"

unsigned long	create_rgb(int t, int r, int g, int b)
{
	return (((t & 0xFF) << 24) + ((r & 0xFF) << 16) + \
			((g & 0xFF) << 8) + (b & 0xFF));
}
