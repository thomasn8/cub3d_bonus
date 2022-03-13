#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>

/* dimensions */
# define WIDTH 900
# define HEIGTH 868
# define MARGIN 5
# define MENU_HEIGTH 100
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
	char			start_player;
	// int				start_x;
	// int				start_y;
	int				m_height;
	int				m_width;
	char			*c_f;
	char			*c_s;
	//////////////////////////////
	int				error;
	int				wall;
	int				free_space;
	int				check_player;
}	t_parse;

// image on game
typedef struct s_image
{
	void			*image;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
}	t_image;

// xpm images
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

// update minimap
typedef struct s_map
{
	int				m_size;
	int				cols;
	int				rows;
	int				x;
	int				y;
	int 			xo;
	int				yo;
	int 			color;
	int 			w;
	int				h;
	int				offset;
	float			prev_x;
	float			prev_y;
	float			pos_x;
	float			pos_y;
	float			delta_x;
	float			delta_y;
	float			a_rad;
	float			a_rad_cpy;
	int				a_deg;
	char			**map;
	unsigned int	**clean_map;
}	t_map;

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
	t_img			menu;
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
}	t_game;

// parsing
int				check_map_name(char *map);
void			save_map(const char *map, t_parse *parse);
int				parsing(int fd, const char *map, t_parse *parse);
void			initialization(t_parse *parse);
int				check_map(void);
int				parse_textures_colors(char *line, t_parse *parse);
char			*save_args(char *line);
void			replace_space_tab(char *str);
int				get_map(t_parse *parse, const char *map);
int				ft_map(char *line, t_parse *parse);
int				ft_is_map(char *line);
void			free_all(t_parse *parse);
int				ft_error(t_parse *parse, char *str, char *line);
int				parse_textures(char *line, t_parse *parse);
int				check_missing(t_parse *parse);
void			check_color(t_parse *parse, char *color);
void			check_texture(t_parse *parse, char *textures);
void			print_map(char **grid);

// init
void			my_mlx_pixel_put(t_image *image, int x, int y, int color);
void			params_init(t_game *game);
void			menu_init(t_game *game);
void			world_init(t_game *game);

// minimap
void			minimap_init(t_game *game, t_parse *parse);
int				move(t_game *game, char move);
int				rotation(t_game *game, char dir);
int				move_ok(t_map *m);

// events
int				quit_prog(t_game *game);
int				key_release(int keycode, t_game *game);
int				key_press(int keycode, t_game *game);
int				events_loop(t_game *game);

#endif
