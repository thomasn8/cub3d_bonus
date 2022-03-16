#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

/* dimensions */
# define WIDTH 960
# define HEIGTH 668
# define MARGIN 5
# define MENU_HEIGTH 120
# define CUBE_SIZE 256

/* colors */
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define GRAY_DARK 0x00202020
# define GRAY_LIGHT 0x00505050
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define YELLOW 0x00FFFF00
/* menu colors */
# define MENU_COLOR GRAY_DARK
# define MENU_TEXT_COLOR WHITE
/* world colors */
# define WORLD_COLOR GRAY_LIGHT

// parsing
typedef struct s_parse
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			view_player;
	int				start_x;
	int				start_y;
	int				m_height;
	int				m_width;
	unsigned long	hex_f;
	unsigned long	hex_s;
	//////////////////////////////
	char			*c_f;
	char			*c_s;
	int				error;
	int				wall;
	int				free_space;
	int				check_player;
	int				r;
	int				g;
	int				b;
	unsigned long	rgb;
}	t_parse;

// image on game (world + minimap)
typedef struct s_image
{
	void			*image;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}	t_image;

// for xpm images
typedef struct	s_img {
	void			*image;
	char			*addr;
	char			*path;
	int				width;
	int				heigth;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
} 	t_img;


// update map
typedef struct s_map
{
	int				m_size;
	float			ws_fps;					// vitesse de jeu (frames per second)
	float			ad_fps;					//
	float			rot_fps;				//
	int				cols;
	int				rows;
	int				x;
	int				y;
	int 			xo;
	int				yo;
	int 			color;
	int 			w;						// width de l'image world dans game
	int				h;						// heigth de l'image world dans game
	int				h_offset;
	int				w_offset;
	float			prev_x;
	float			prev_y;
	float			pos_x;					// x position du player
	float			pos_y;					// y position du player
	float			delta_x;
	float			delta_y;
	float			a_rad;					// view_player (en radius)
	float			player_angle;
	int				a_deg;					// view_player (en degré)
	char			cross;
	char			**map;					// map
	unsigned int	**clean_map;
	char			*no;					// textures ...
	char			*so;					//
	char			*we;					//
	char			*ea;					//
	int				c_floor;				// couleur sol
	int				c_ceil;					// couleur plafond
}	t_map;

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
	int		shift;
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
	char	cross;
	int		l;
	float	top;
	float	bot;
	int		lpr;
	int		color;
	int		p_y;
}	t_rays;

typedef struct s_grid
{
	int		of;
	int		xo;
	int		yo;
	int		vo;
	int		ho;
	int		mx;
	int		mx_add_xo;
	int		mx_sub_xo;
	int		my;
	int		my_add_yo;
	int		my_sub_yo;
}	t_grid;

// game
typedef struct s_game
{
	void			*mlx;
	void			*win;
	int				width;
	int				heigth;
	int				world_h;
	t_image			world;
	t_image			map;
	t_map			m;
	t_rays			r;
	t_grid			g;
	// t_img			menu;
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
}	t_game;

// parsing
int				check_name(char *map, char *correct_ext);
void			save_map(const char *map, t_parse *parse);
int				parsing(int fd, const char *map, t_parse *parse);
void			initialisation(t_parse *parse);
int				check_map(void);
int				parse_textures_colors(char *line, t_parse *parse);
char			*save_args(char *line);
void			replace_space_tab(char *str);
void			get_map(t_parse *parse, const char *map);
void			get_map2(int l, int i, t_parse *parse);
int				ft_map(char *line, t_parse *parse);
int				ft_is_map(char *line);
void			free_all(t_parse *parse);
int				ft_error(t_parse *parse, char *str, char *line);
int				parse_textures(char *line, t_parse *parse);
int				check_missing(t_parse *parse);
void			check_color(t_parse *parse, char *color, char c);
int				check_error_texture(t_parse *parse, char *textures);
void			print_map(char **grid);
unsigned long	create_rgb(int t, int r, int g, int b);
void			print_all(t_parse *p);

// init
void			params_init(t_game *game);
void			menu_init(t_game *game);
void			world_init(t_game *game);
void			minimap_init(t_game *game, t_parse *parse);

// minimap
void			map_description(t_game *game, t_parse *parse);
void			player_description(t_game *game, t_parse *parse);
void			color_map(t_image *map, t_map *m);
unsigned int	**copy_map(t_image *map, int width, int heigth);
void			rotation(t_game *game, char dir);
void			move(t_game *game, char move);
void			draw_all(t_game *game, char t);



// events
void			my_mlx_pixel_put(t_image *image, int x, int y, int color);
int				quit_prog(t_game *game);
int				key_release(int keycode, t_game *game);
int				key_press(int keycode, t_game *game);
int				events_loop(t_game *game);

#endif
