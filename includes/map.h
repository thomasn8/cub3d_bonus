#ifndef MAP_H
# define MAP_H

# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define GRAY_DARK 0x00202020
# define GRAY_LIGHT 0x00505050
# define PURPLE 0x006C0277
# define CV1 0x00101010
# define CV2 0x00202020
# define CH1 0x00303030
# define CH2 0x00000000
# define SKY 0x006600FF
# define GROUND 0x00505050
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00

# define M_PLAYER_SIZE 3
# define M_PS 3
# define M_WALL_COLOR GRAY_LIGHT
# define M_DOOR_COLOR GRAY_DARK
# define M_SPACE_COLOR BLACK
# define M_GRID_COLOR PURPLE
# define M_PLAYER_COLOR YELLOW
# define M_FOV_COLOR GREEN
# define M_HALF_PLAYER (M_PLAYER_SIZE / 2)
# define PI 3.1415926535
# define PI2 6.2831853071
# define M_1_DEG_RAD 0.017453293	// (2*pi)/360
# define M_EAST 0
# define M_NORTH 90
# define M_WEST 180
# define M_SOUTH 270
# define M_RAD_0 0
# define M_RAD_90 1.57079632679		// = pi/2
# define M_RAD_180 3.1415926535		// = pi
# define M_RAD_270 4.71238898038	// = 3*pi/2

/* MINIMAP */
// player
void			collision_check(t_map *m, t_grid *g, char k);
void			new_pos(t_image *map, t_map *m, int color);
void			new_fov(t_image *map, t_map *m);
void			remove_prev_fov(t_image *map, t_map *m);

/* RAYCASTING */
// ray_dist
void			ray_horizontal_check(t_map *m, t_rays *r);
void			ray_vertical_check(t_map *m, t_rays *r);
// raycasting
void			raycasting(t_game *game);
// rc_utils
void			check_angle(float angle, int *deg);
void			compare_dist(t_rays	*r, int m_size);
void			draw_v_line(t_image *image, t_rays *r, int color);
float			fix_fisheye(float angle);
void			draw_ray(t_image *image, t_map *m, t_rays *r, int color);
// textures
void			v_textures_init(t_rays *r, t_game *game);
void			h_textures_init(t_rays *r, t_game *game);
void			bonus_textures_init(t_rays *r, t_game *game);
t_img			*ray_texture(float ray_a, t_rays *r);
int				ray_color(float ray_a, t_rays *r);

#endif
