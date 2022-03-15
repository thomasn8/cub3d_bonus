#include "../includes/cub3d.h"
#include "../includes/map.h"

void	cast_single_ray(t_game *game)
{
	game->m.player_angle = game->m.a_rad;
	game->r.dist_v = 10000000;
	game->r.dist_h = 10000000;
	game->r.atan = -1 / tan(-game->m.a_rad);
	game->r.ntan = -tan(-game->m.a_rad);
	ray_horizontal_check(&game->m, &game->r);
	ray_vertical_check(&game->m, &game->r);
	// game->m.cross = compare_dist(&game->r);	
	// printf("%c\n", game->m.cross);
}

int	move_check(t_game *game)
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;
	int				walls;

	x1 = (game->m.pos_x - 1) / game->m.m_size;
	y1 = (game->m.pos_y - 1) / game->m.m_size;
	x2 = (game->m.pos_x + M_PLAYER_SIZE - 1) / game->m.m_size;
	y2 = (game->m.pos_y + M_PLAYER_SIZE - 1) / game->m.m_size;
	
	walls = 0;
	if (game->m.map[(int)y1][(int)x1] == '1')
		walls++;
	if (game->m.map[(int)y2][(int)x2] == '1')
		walls++;
	if (game->m.map[(int)y1][(int)x2] == '1')
		walls++;
	if (game->m.map[(int)y2][(int)x1] == '1')
		walls++;
	if (walls == 0)
		return (1);

	cast_single_ray(game);							// wall a proximité -> check quelle face

	printf("Walls: %d (%f, %f)\n", walls, game->m.pos_x, game->m.pos_y);
	if (game->m.cross == 'v') 						// player contre un mur vertical
	{
		x1 = (game->m.prev_x - 1) / game->m.m_size;
		x2 = (game->m.prev_x + M_PLAYER_SIZE - 1) / game->m.m_size;
		if (game->m.map[(int)y1][(int)x1] != '1' &&
			game->m.map[(int)y2][(int)x2] != '1' &&
			game->m.map[(int)y1][(int)x2] != '1' &&
			game->m.map[(int)y2][(int)x1] != '1')
		{
			if (walls < 3)
			{
				game->m.pos_x = game->m.prev_x;
				return (1);
			}
			else
			{
				game->m.pos_x = game->m.prev_x;
				game->m.pos_y = game->m.prev_y;
				return (0);
			}
		}
	}
	else if (game->m.cross == 'h') 						// player contre un mur horizontal
	{
		y1 = (game->m.prev_y - 1) / game->m.m_size;
		y2 = (game->m.prev_y + M_PLAYER_SIZE - 1) / game->m.m_size;
		if (game->m.map[(int)y1][(int)x1] != '1' &&
			game->m.map[(int)y2][(int)x2] != '1' &&
			game->m.map[(int)y1][(int)x2] != '1' &&
			game->m.map[(int)y2][(int)x1] != '1')
		{
			if (walls < 3)
			{
				game->m.pos_y = game->m.prev_y;
				return (1);
			}
			else
			{
				game->m.pos_x = game->m.prev_x;
				game->m.pos_y = game->m.prev_y;
				return (0);
			}
		}
	}
	return (0);
}

int	count_walls(t_game *game)
{
	float			x1;
	float			y1;
	float			x2;
	float			y2;
	int				walls;

	x1 = (game->m.pos_x - 1) / game->m.m_size;
	y1 = (game->m.pos_y - 1) / game->m.m_size;
	x2 = (game->m.pos_x + M_PLAYER_SIZE - 1) / game->m.m_size;
	y2 = (game->m.pos_y + M_PLAYER_SIZE - 1) / game->m.m_size;
	
	walls = 0;
	if (game->m.map[(int)y1][(int)x1] == '1')
		walls++;
	if (game->m.map[(int)y2][(int)x2] == '1')
		walls++;
	if (game->m.map[(int)y1][(int)x2] == '1')
		walls++;
	if (game->m.map[(int)y2][(int)x1] == '1')
		walls++;
	return(walls);
}