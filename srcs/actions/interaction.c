#include "../../includes/cub3d.h"
#include "../../includes/map.h"

static void	v_door(t_game *game, int x, int y)
{
	if (game->m.map[y][x] == '4')
	{
		game->m.map[y][x] = '5';
		if (game->m.map[y - 1][x] == '3')
			game->m.map[y - 1][x] = '9';
		if (game->m.map[y + 1][x] == '3')
			game->m.map[y + 1][x] = '9';
		if (game->m.map[y - 1][x] == '9' || game->m.map[y + 1][x] == '9')
			game->interact = 1;
	}
	else if (game->m.map[y][x] == '5')
	{
		game->m.map[y][x] = '4';
		if (game->m.map[y - 1][x] == '9')
			game->m.map[y - 1][x] = '3';
		if (game->m.map[y + 1][x] == '9')
			game->m.map[y + 1][x] = '3';
		if (game->m.map[y - 1][x] == '3' || game->m.map[y + 1][x] == '3')
			game->interact = 1;
	}
}

static void	h_door(t_game *game, int x, int y)
{
	if (game->m.map[y][x] == '4')
	{
		game->m.map[y][x] = '5';
		if (game->m.map[y][x - 1] == '3')
			game->m.map[y][x - 1] = '9';
		if (game->m.map[y][x + 1] == '3')
			game->m.map[y][x + 1] = '9';
		if (game->m.map[y][x - 1] == '9' || game->m.map[y][x + 1] == '9')
			game->interact = 1;
	}
	else if (game->m.map[y][x] == '5')
	{
		game->m.map[y][x] = '4';
		if (game->m.map[y][x - 1] == '9')
			game->m.map[y][x - 1] = '3';
		if (game->m.map[y][x + 1] == '9')
			game->m.map[y][x + 1] = '3';
		if (game->m.map[y][x - 1] == '3' || game->m.map[y][x + 1] == '3')
			game->interact = 1;
	}
}

static void	get_ray(t_game *game)
{
	if (game->r.dist_v != 0 && (game->r.dist_h == 0 || game->r.dist_v < game->r.dist_h))
	{
		game->r.x = game->r.vx;
		game->r.y = game->r.vy;
		game->r.wx = game->r.x / game->m.m_size;
		game->r.wy = game->r.y / game->m.m_size;
		game->r.dist = game->r.dist_v;
		game->r.cross = 'v';
		if (game->r.dist / game->m.m_size < 1)
			v_door(game, game->r.vmx + game->r.v_shift, game->r.vmy);
	}
	else
	{
		game->r.x = game->r.hx;
		game->r.y = game->r.hy;
		game->r.wx = game->r.x / game->m.m_size;
		game->r.wy = game->r.y / game->m.m_size;
		game->r.dist = game->r.dist_h;
		game->r.cross = 'h';
		if (game->r.dist / game->m.m_size < 1)
			h_door(game, game->r.hmx + game->r.v_shift, game->r.hmy + game->r.h_shift);
	}
}

void	interaction(t_game *game)
{
	game->interact = 0;
	game->m.player_angle = game->m.a_rad;
	game->r.dist_v = 0;
	game->r.dist_h = 0;
	game->r.atan = -1 / tan(-game->m.a_rad);
	game->r.ntan = -tan(-game->m.a_rad);
	game->r.spe = '0';
	ray_horizontal_check(&game->m, &game->r);
	ray_vertical_check(&game->m, &game->r);
	get_ray(game);
	if (game->interact)
	{
		color_map(&game->map, &game->m);
		ft_free_array((void **)game->m.clean_map);
		game->m.clean_map = copy_map(&game->map, game->m.w, game->m.h);
		draw_all(game, '2');
	}
}
