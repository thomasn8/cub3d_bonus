/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 08:34:35 by tnanchen          #+#    #+#             */
/*   Updated: 2022/03/24 20:16:39 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../mlx/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <fcntl.h>
# include <CoreGraphics/CGDisplayConfiguration.h>

/* dimensions */
# define FOV 60
# define M_RAY_FACTOR 8
# define WIDTH 960
# define HEIGTH 800
# define MARGIN 5
# define MENU_HEIGTH 120
# define W_TEX '6'

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
typedef struct s_img {
	void			*image;
	char			*addr;
	char			*path;
	int				width;
	int				heigth;
	int				bpp;
	int				ll;
	int				e;
}	t_img;

// update map
typedef struct s_map
{
	int				m_size;
	float			ws_fps;
	float			ad_fps;
	float			rot_fps;
	int				cols;
	int				rows;
	int				x;
	int				y;
	int				xo;
	int				yo;
	int				color;
	int				w;
	int				h;
	int				h_offset;
	int				w_offset;
	float			prev_x;
	float			prev_y;
	float			pos_x;
	float			pos_y;
	float			delta_x;
	float			delta_y;
	float			a_rad;
	float			player_angle;
	int				a_deg;
	char			cross;
	char			**map;
	unsigned int	**clean_map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	int				c_floor;
	int				c_ceil;
}	t_map;

// raycasting calculations
typedef struct s_rays
{
	int				rays;
	int				r_1;
	int				r_05;
	double			r_ra;
	double			fov_05;
	float			atan;
	float			ntan;
	float			x;
	float			y;
	float			xo;
	float			yo;
	int				i;
	int				v_shift;
	int				h_shift;
	int				rows;
	int				cols;
	int				vmx;
	int				vmy;
	int				hmx;
	int				hmy;
	float			hx;
	float			hy;
	float			vx;
	float			vy;
	float			wx;
	float			wy;
	float			dist_h;
	float			dist_v;
	float			dist;
	char			cross;
	char			spe;
	float			w_bot;
	float			w_top;
	int				lpr;
	int				lpr_cpy;
	int				color;
	float			shade;
	int				ix;
	int				iy;
	int				x1;
	int				y1;
	int				x2;
	int				y2;
	t_img			tex_n;
	t_img			tex_s;
	t_img			tex_e;
	t_img			tex_w;
	t_img			tex_flag;
	t_img			tex_steel;
	t_img			tex_biblio;
	t_img			tex_iu;
	t_img			tex_id;
	t_img			*tex;
	char			char_map;
	float			tx;
	float			ty;
	float			tx_step;
	float			ty_step;
	float			to;
	float			tc;
	unsigned int	c;
}	t_rays;

// slide moves
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

// pour dessiner viseur
typedef struct s_point
{
	int				i;
	int				o;
	int				x1;
	int				y1;
	int				x2;
	int				y2;
}	t_point;

// game
typedef struct s_game
{
	void			*mlx;
	void			*win;
	CGDirectDisplayID	display;
	int				win_w;
	int				win_h;
	int				margin_w;
	int				margin_h;
	int				width;
	int				heigth;
	int				world_h;
	t_image			world;
	t_image			map;
	t_parse			*parse;
	t_map			m;
	t_rays			r;
	t_grid			g;
	int				w;
	int				s;
	int				a;
	int				d;
	int				left;
	int				right;
	int				interact;
	int				weapon;
	int				state;
	t_img			tex_kat_run;
	int				kat_run_mw;
	int				kat_run_mh;
	t_img			tex_kat_hit;
	int				kat_hit_mw;
	int				kat_hit_mh;
	t_img			tex_kat_def;
	int				kat_def_mw;
	int				kat_def_mh;
	t_img			tex_gun_run;
	int				gun_run_mw;
	int				gun_run_mh;
	int				gun_shoot_mw;
	int				gun_shoot_mh;
	t_point			p;
}	t_game;

// parsing
int				check_name(char *map, char *correct_ext);
void			save_map(const char *map, t_parse *parse);
int				parsing(int fd, const char *map, t_parse *parse);
void			initialisation(t_parse *parse);
int				parse_textures_colors(char *line, t_parse *parse);
char			*save_args(char *line);
void			replace_space_tab(char **map);
void			get_map(t_parse *parse, const char *map);
void			get_map2(int l, int i, t_parse *parse);
void			get_map3(t_parse *parse);
int				ft_map(char *line, t_parse *parse);
int				ft_is_map(t_parse *parse, char *line);
void			free_all(t_parse *parse);
int				ft_error(t_parse *parse, char *str, char *line);
int				parse_textures(char *line);
int				check_missing(t_parse *parse);
void			check_color(t_parse *parse, char *color, char c);
void			print_map(char **grid);
unsigned long	create_rgb(int t, int r, int g, int b);
void			print_all(t_parse *p);
void			check_error(t_parse *parse);
int				check_map_close(t_parse *parse, char *str);
void			get_color(int nbr, int sum, t_parse *parse, char c);
void			get_map3(t_parse *parse);

// utils
float			deg_to_rad(int angle);
int				rad_to_deg(float angle);
unsigned int	get_color_value(t_image *image, int x, int y);
unsigned int	get_tex_color(t_img *tex, int x, int y, float shade);
void			texture_error(void *image, char *msg);

// init
void			window_init(t_game *game);
void			game_init(t_game *game);
void			world_init(t_game *game);
void			minimap_init(t_game *game, t_parse *parse);
void			tex_kat_create1(t_game *game);
void			tex_kat_create2(t_game *game);
void			tex_gun_create(t_game *game);

// minimap
void			map_description(t_game *game, t_parse *parse);
void			color_map(t_image *map, t_map *m);
unsigned int	**copy_map(t_image *map, int width, int heigth);
void			rotation(t_game *game, char dir);
void			move(t_game *game, char move);
void			draw_all(t_game *game, char t);
int				map_char(char c);

// actions
void			weapons_dimensions(t_game *game);
void			weapon_display(t_game *game);
void			weapon_press(int k, t_game *game);
void			weapon_release(int k, t_game *game);
void			draw_viewfinder(t_game *game);
void			kat_attack(t_game *game, char k);
void			kat_defense(t_game *game, char k);
void			gun_shoot(t_game *game, char k);
void			interaction(t_game *t_game);

// enemies
void			enemies_init(t_game *game, t_map *m);
void			tex_enemies_create(t_game *game);

// events
void			my_mlx_pixel_put(t_image *image, int x, int y, int color);
int				quit_prog(t_game *game);
int				key_release(int k, t_game *game);
int				key_press(int k, t_game *game);
int				events_loop(t_game *game);

// mouse
int				mouse_press(int button, int x, int y, t_game *game);
int				mouse_release(int button, int x, int y, t_game *game);
int				mouse_move(int mx, int my, t_game *game);

#endif
