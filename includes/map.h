#ifndef MAP_H
# define MAP_H

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define GRAY_DARK 0x00202020
# define GRAY_LIGHT 0x00505050
# define PURPLE 0x006C0277
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00

// small
# define M_SIZE 16
# define M_PLAYER_SIZE 5
// big
// # define M_SIZE 64
// # define M_PLAYER_SIZE 9

# define M_WALL_COLOR GRAY_LIGHT
# define M_SPACE_COLOR BLACK
# define M_GRID_COLOR PURPLE
# define M_PLAYER_COLOR YELLOW
# define M_FOV_COLOR GREEN
# define M_FOV_SIZE (3 * M_PLAYER_SIZE)
# define M_HALF_PLAYER (M_PLAYER_SIZE / 2)
# define M_DISTANCE 1
# define PI 3.1415926535
# define M_1_DEG_RAD 0.0174533
# define M_RAYS 60
# define M_HALF_RAYS (M_RAYS / 2)
# define M_EAST 0
# define M_NORTH 90
# define M_WEST 180
# define M_SOUTH 270
# define M_RAD_0 0
# define M_RAD_90 PI / 2
# define M_RAD_180 PI
# define M_RAD_270 (3 * PI / 2)

typedef struct s_rays
{
	int		rays;
	float	atan;
	float	ntan;
	float	x;
	float	y;
	float	xo;
	float	yo;
	int		i;
	int		rows;
	int		cols;
	int		mx;
	int		my;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	float	dist_h;
	float	dist_v;
	float	dist;
}	t_rays;

float		deg_to_rad(int angle);
int			rad_to_deg(float angle);

void		check_angle(float angle, int *deg);
void		init_casting(t_rays *r, float angle);
float		distance(t_map *m, t_rays *r);
void		compare_dist(t_rays	*r);
void		draw_ray(t_image *image, t_map *m, t_rays *r, int color);

void		new_player_pos(t_image *map, t_map *m, int color);
void		new_player_fov(t_image *map, t_map *m);
void		remove_prev_pos(t_image *map, t_map *m);
void		remove_prev_fov(t_image *map, t_map *m);

int			move_s(t_map *m);
int			move_d(t_map *m);
int			move_w(t_map *m);
int			move_a(t_map *m);

#endif
