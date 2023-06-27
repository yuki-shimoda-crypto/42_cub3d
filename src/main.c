/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/22 14:47:51 by yshimoda         ###   ########.fr       */
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

// #include <stdio.h>
// #include <mlx.h>
// 
// #define WIN_WIDTH 640
// #define WIN_HEIGHT 480
// 
// #define MAP_WIDTH 24
// #define MAP_HEIGHT 24
// 
// #define TILE_SIZE 20 // Size of each square tile (20 pixels in this case)
// 
// void	*safe_mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
// {
// 	void	*mlx_ptr_win;
// 
// 	mlx_ptr_win = mlx_new_window(mlx_ptr, size_x, size_y, title);
// 	if (!mlx_ptr_win)
// 		exit_error("mlx new window is failed\n", false);
// 	return (mlx_ptr_win);
// }
// 
// void	*safe_mlx_init(void)
// {
// 	void	*mlx_ptr;
// 
// 	mlx_ptr = mlx_init();
// 	if (!mlx_ptr)
// 		exit_error("mlx init is failed\n", false);
// 	return (mlx_ptr);
// }

// int worldMap[MAP_HEIGHT][MAP_WIDTH] = {
//    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };

//int main()
//{
//	void *mlx_ptr;
//	void *mlx_win_ptr;
//	
//	mlx_ptr = safe_mlx_init();
//	mlx_win_ptr = safe_mlx_new_window(mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "Raycaster");
//	for (int y = 0; y < MAP_HEIGHT; y++)
//	{
//	  for (int x = 0; x < MAP_WIDTH; x++)
//	  {
//	    if (worldMap[y][x] == 0)
//	    {
//	      mlx_pixel_put(mlx_ptr, mlx_win_ptr, x*TILE_SIZE, y*TILE_SIZE, 0x00FF0000);
//	    }
//	    else if (worldMap[y][x] == 1)
//	    {
//	      mlx_pixel_put(mlx_ptr, mlx_win_ptr, x*TILE_SIZE, y*TILE_SIZE, 0x0000FF00);
//	    }
//	  }
//	}
//	mlx_loop(mlx_ptr);
//	return 0;
//}


#include <stdio.h>
#include <math.h>

#define TILE_SIZE 64
#define PLAYER_SIZE 64
#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
#define MAP_NUM_ROWS 16
#define MAP_NUM_COLS 16
#define NUM_RAYS WINDOW_WIDTH
// #define FOV_ANGLE (60 * (M_PI / 180))

typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_mlx	t_mlx;

struct s_player {
    float x;
    float y;
    float width;
    float height;
};

struct s_ray{
    float x;
    float y;
    float ray_angle;
    float distance;
    int is_vertical;
};

struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
};

// float	player.rotationAngle = PI / 2;
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

void	*safe_mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title)
{
	void	*win_ptr;

	win_ptr = mlx_new_window(mlx_ptr, size_x, size_y, title);
	if (!win_ptr)
		exit_error("mlx new window is failed\n", false);
	return (win_ptr);
}

void	*safe_mlx_init(void)
{
	void	*mlx_ptr;

	mlx_ptr = mlx_init();
	if (!mlx_ptr)
		exit_error("mlx init is failed\n", false);
	return (mlx_ptr);
}

int	main(void)
{
	t_mlx		mlx;
	t_player	player;

	mlx.mlx_ptr = safe_mlx_init();
	mlx.win_ptr = safe_mlx_new_window(mlx.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "test");
	player.x = WINDOW_WIDTH / 2;
	player.y = WINDOW_HEIGHT / 2;
	draw_map_and_player(&mlx, &player);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, event_key_press, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 2, destroy_mlx, &mlx);
	mlx_loop(mlx.mlx_ptr);
}
