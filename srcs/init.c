/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tnanchen <thomasnanchen@hotmail.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 07:49:55 by tnanchen          #+#    #+#             */
/*   Updated: 2022/03/24 21:03:01 by tnanchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "../includes/map.h"

static void	player_description(t_game *game, t_parse *parse)
{
	game->m.pos_x = (parse->start_x * game->m.m_size)
		+ (0.5 * game->m.m_size) - (0.5 * M_PLAYER_SIZE);
	game->m.pos_y = (parse->start_y * game->m.m_size)
		+ (0.5 * game->m.m_size) - (0.5 * M_PLAYER_SIZE);
	game->m.prev_x = game->m.pos_x;
	game->m.prev_y = game->m.pos_y;
	if (parse->view_player == 'E')
		game->m.a_rad = deg_to_rad(M_EAST);
	else if (parse->view_player == 'N')
		game->m.a_rad = deg_to_rad(M_NORTH);
	else if (parse->view_player == 'W')
		game->m.a_rad = deg_to_rad(M_WEST);
	else if (parse->view_player == 'S')
		game->m.a_rad = deg_to_rad(M_SOUTH);
	game->m.a_deg = rad_to_deg(game->m.a_rad);
	game->m.delta_x = cos(-game->m.a_rad);
	game->m.delta_y = sin(-game->m.a_rad);
}

void	minimap_init(t_game *game, t_parse *parse)
{
	game->parse = parse;
	map_description(game, parse);
	h_textures_init(&game->r, game);
	v_textures_init(&game->r, game);
	tex_door_create(&game->r, game);
	tex_interuptor_create(&game->r, game);
	tex_deco_create(&game->r, game);
	weapons_dimensions(game);
	player_description(game, parse);
	color_map(&game->map, &game->m);
	game->m.clean_map = copy_map(&game->map, game->m.w, game->m.h);
	draw_all(game, '1');
}

// + on augmente ray_factor, + on lance de rayon, + on a des textures détaillées
void	world_init(t_game *game)
{
	int	x;
	int	y;

	game->world.image = mlx_new_image(game->mlx, game->width, game->world_h);
	game->world.addr = mlx_get_data_addr(game->world.image,
			&game->world.bits_per_pixel, &game->world.line_length,
			&game->world.endian);
	y = -1;
	while (++y < game->world_h)
	{
		x = -1;
		while (++x < game->width)
			my_mlx_pixel_put(&game->world, x, y, WORLD_COLOR);
	}
	game->r.r_1 = FOV * M_RAY_FACTOR;
	game->r.r_05 = game->r.r_1 / 2;
	game->r.r_ra = (M_1_DEG_RAD / M_RAY_FACTOR);
	game->r.fov_05 = game->r.r_05 * game->r.r_ra;
	tex_kat_create1(game);
	tex_kat_create2(game);
	tex_gun_create(game);
}

void	game_init(t_game *game)
{
	game->width = WIDTH;
	game->heigth = HEIGTH;
	game->world_h = HEIGTH - MENU_HEIGTH;
	game->w = 0;
	game->s = 0;
	game->a = 0;
	game->d = 0;
	game->left = 0;
	game->right = 0;
	game->weapon = 1;
	game->state = 0;
	game->m.ws_fps = 1;
	game->m.ad_fps = 0.75;
	game->m.rot_fps = 10;
	game->mouse_x = game->win_w / 15;
	game->mouse_y = game->win_h;
}

void	window_init(t_game *game)
{
	game->mlx = mlx_init();
	game->display = CGMainDisplayID();
	game->win_w = 0;
	game->win_h = 0;
	game->win_w = CGDisplayPixelsWide(game->display);
	game->win_h = CGDisplayPixelsHigh(game->display);
	if (game->win_w > 0 && game->win_h > 0)
	{
		game->margin_w = (game->win_w - WIDTH) / 2;
		game->margin_h = (game->win_h - HEIGTH) / 2;
	}
	else
	{
		game->win_w = WIDTH;
		game->win_h = HEIGTH;
		game->margin_w = 0;
		game->margin_h = 0;
	}
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "cub3d");
	mlx_string_put(game->mlx, game->win, game->win_w / 2 - 30,
		game->margin_h - 30, MENU_TEXT_COLOR, "CUB3D");
}
