/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/30 16:16:45 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>

// static void	init_game_data(t_game_data *data)
// {
// 	data->map_node = NULL;
// 	data->player_pos = NULL;
// 	data->orientation = '\0';
// 	data->n_texture = NULL;
// 	data->s_texture = NULL;
// 	data->w_texture = NULL;
// 	data->e_texture = NULL;
// 	data->f_color[0] = 0;
// 	data->f_color[1] = 0;
// 	data->f_color[2] = 0;
// 	data->c_color[0] = 0;
// 	data->c_color[1] = 0;
// 	data->c_color[2] = 0;
// }
// 
// int	main(int argc, const char *argv[])
// {
// 	t_cub_file_node		*cub_file_node;
// 	t_game_data			data;
// 
// 	init_game_data(&data);
// 	check_file_name(argc, argv);
// 	cub_file_node = read_cub_file(argv[1]);
// 	check_cub_file(cub_file_node, &data);
// 	free_cub_file_node(cub_file_node);
// 	free_data(&data);
// 	return (0);
// }

#include <stdio.h>
#include <math.h>

#define TILE_SIZE 64
#define PLAYER_SIZE 64
#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
#define MAP_NUM_ROWS 16
#define MAP_NUM_COLS 16
#define NUM_RAYS WINDOW_WIDTH
#define FOV_ANGLE (60 * (M_PI / 180))

typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_mlx	t_mlx;

struct s_player {
    float	x;
    float	y;
	float	rotationAngle;
};

struct s_ray{
    float	x;
    float	y;
    float	ray_angle;
    float	distance;
    int		is_vertical;
};

struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
};

// 
// Ray rays[WINDOW_WIDTH];


int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};


void	draw_map_and_player(t_mlx *mlx, t_player *player)
{
	int	i;
	int	j;
	int	x;
	int	y;
	int	color;

	i = 0;
	while (i < MAP_NUM_ROWS)
	{
		j = 0;
		while (j < MAP_NUM_COLS)
		{
			if (map[i][j] == 1)
				color = 0xFFFFFF;
			else
				color = 0x000000;
			y = i * TILE_SIZE;
			while (y < (i + 1) * TILE_SIZE)
			{
				x = j * TILE_SIZE;
				while (x < (j + 1) * TILE_SIZE)
				{
					mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);
					x++;
				}
				y++;
			}
			j++;
		}
		i++;
	}
	y = player->y - PLAYER_SIZE / 2;
	while (y < player->y + PLAYER_SIZE / 2)
	{
		x = player->x - PLAYER_SIZE / 2;
		while (x < player->x + PLAYER_SIZE / 2)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

int	destroy_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

int	event_key_press(int key_num, t_mlx *mlx)
{
	if (key_num == KEY_ESC)
		destroy_mlx(mlx);
	return (0);
}

int	ray_casting(void *mlx)
{
}

int	main(void)
{
	t_mlx		mlx;
	t_player	player;

	mlx.mlx_ptr = safe_mlx_init();
	mlx.win_ptr = safe_mlx_new_window(mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "test");
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;
	player.rotationAngle = PI / 2;
	draw_map_and_player(&mlx, &player);

//	for (int i = 0; i < NUM_RAYS; i++)
//	{
//		float	distanceToWall = castRay(rayAngle);
//		rayAngle += FOV_ANGLE / NUM_RAYS;
//	}






	mlx_loop_hook(mlx_ptr, ray_casting, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, event_key_press, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 2, destroy_mlx, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
