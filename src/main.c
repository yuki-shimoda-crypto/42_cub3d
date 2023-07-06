/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/06 20:25:56 by yshimoda         ###   ########.fr       */
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
// #include <math.h>
// 
// #define TILE_SIZE 64
// #define PLAYER_SIZE 64
// #define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
// #define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)
// #define MAP_NUM_ROWS 16
// #define MAP_NUM_COLS 16
// #define NUM_RAYS WINDOW_WIDTH
// #define FOV_ANGLE (60 * (M_PI / 180))
// 
// typedef struct s_player	t_player;
// typedef struct s_ray	t_ray;
// typedef struct s_mlx	t_mlx;
// 
// struct s_player {
//     double	x;
//     double	y;
// 	double	rotationAngle;
// };
// 
// struct s_ray{
//     double	x;
//     double	y;
//     double	ray_angle;
//     double	distance;
//     int		is_vertical;
// };
// 
// struct s_mlx
// {
// 	void		*mlx_ptr;
// 	void		*win_ptr;
// 	t_player	*player;
// 	double		posX;
// 	double		posY;
// 	double		dirX;
// 	double		dirY;
// 	double		planeX;
// 	double		planeY;
// 
// };
// 
// // 
// // Ray rays[WINDOW_WIDTH];
// 
// 
// int map[MAP_NUM_ROWS][MAP_NUM_COLS] = {
//    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
//    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
// };
// 
// 
// void	draw_map_and_player(t_mlx *mlx, t_player *player)
// {
// 	int	i;
// 	int	j;
// 	int	x;
// 	int	y;
// 	int	color;
// 
// 	i = 0;
// 	while (i < MAP_NUM_ROWS)
// 	{
// 		j = 0;
// 		while (j < MAP_NUM_COLS)
// 		{
// 			if (map[i][j] == 1)
// 				color = 0xFFFFFF;
// 			else
// 				color = 0x000000;
// 			y = i * TILE_SIZE;
// 			while (y < (i + 1) * TILE_SIZE)
// 			{
// 				x = j * TILE_SIZE;
// 				while (x < (j + 1) * TILE_SIZE)
// 				{
// 					mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);
// 					x++;
// 				}
// 				y++;
// 			}
// 			j++;
// 		}
// 		i++;
// 	}
// 	y = player->y - PLAYER_SIZE / 2;
// 	while (y < player->y + PLAYER_SIZE / 2)
// 	{
// 		x = player->x - PLAYER_SIZE / 2;
// 		while (x < player->x + PLAYER_SIZE / 2)
// 		{
// 			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, 0xFF0000);
// 			x++;
// 		}
// 		y++;
// 	}
// }
// 
// int	destroy_mlx(t_mlx *mlx)
// {
// 	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
// 	exit(EXIT_SUCCESS);
// 	return (0);
// }
// 
// int	event_key_press(int key_num, t_mlx *mlx)
// {
// 	if (key_num == KEY_ESC)
// 		destroy_mlx(mlx);
// 	return (0);
// }
// 
// void	write_line(t_mlx *mlx, int x, int start, int end, int color)
// {
// 	int		y;
// 
// 	y = start;
// 	while (y < end)
// 	{
// 		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);
// 		y++;
// 	}
// }
// 
// int	ray_casting(void *mlx)
// {
// 	int		x;
// 	double	cameraX;
// 	double	rayDirX;
// 	double	rayDirY;
// 	int		mapX;
// 	int		mapY;
// 	double	sideDistX;
// 	double	sideDistY;
// 	double	deltaDistX;
// 	double	deltaDistY;
// 	double	perpWallDist;
// 	int		stepX;
// 	int		stepY;
// 	int		hit;
// 	int		side;
// 	int		lineHeight;
// 	int		drawStart;
// 	int		drawEnd;
// 	int		color;
// 
// 	hit = 0;
// 	x = 0;
// 	while (x < NUM_RAYS)
// 	{
// 		cameraX = 2 * x / (double)(NUM_RAYS) - 1;
// 		rayDirX = ((t_mlx *)mlx)->dirX + ((t_mlx *)mlx)->planeX * cameraX;
// 		rayDirY = ((t_mlx *)mlx)->dirY + ((t_mlx *)mlx)->planeY * cameraX;
// 		mapX = ((t_mlx *)mlx)->posX;
// 		mapY = ((t_mlx *)mlx)->posY;
// 		deltaDistX = fabs(1 / rayDirX);
// 		deltaDistY = fabs(1 / rayDirY);
// 		if (rayDirX < 0)
// 		{
// 			stepX = -1;
// 			sideDistX = (((t_mlx *)mlx)->posX - mapX) * deltaDistX;
// 		}
// 		else
// 		{
// 			stepX = 1;
// 			sideDistX = (mapX + 1.0 - ((t_mlx *)mlx)->posX) * deltaDistX;
// 		}
// 		if (rayDirY < 0)
// 		{
// 			stepY = -1;
// 			sideDistY = (((t_mlx *)mlx)->posY - mapY) * deltaDistY;
// 		}
// 		else
// 		{
// 			stepY = 1;
// 			sideDistY = (mapY + 1.0 - ((t_mlx *)mlx)->posY) * deltaDistY;
// 		}
// 		while (hit == 0)
// 		{
// 			if (sideDistX < sideDistY)
// 			{
// 				sideDistX += deltaDistX;
// 				mapX += stepX;
// 				side = 0;
// 			}
// 			else
// 			{
// 				sideDistY += deltaDistY;
// 				mapY += stepY;
// 				side = 1;
// 			}
// 			if (map[mapY][mapX])
// 				hit = 1;
// 		}
// 		if (side == 0)
// 			perpWallDist = (mapX - ((t_mlx *)mlx)->posX + (1 - stepX) / 2) / rayDirX;
// 		else
// 			perpWallDist = (mapY - ((t_mlx *)mlx)->posY + (1 - stepY) / 2) / rayDirY;
// 		lineHeight = (int)(WINDOW_HEIGHT / perpWallDist);
// 		drawStart = -lineHeight / 2 + WINDOW_HEIGHT / 2;
// 		if (drawStart < 0)
// 			drawStart = 0;
// 		drawEnd = lineHeight / 2 + WINDOW_HEIGHT / 2;
// 		if (drawEnd > WINDOW_HEIGHT)
// 			drawEnd = WINDOW_HEIGHT;
// 		if (map[mapY][mapX] == 1)	
// 			color = 0x0000FF;
// 		else
// 			color = 0x000000;
// 		if (side == 1)
// 			color = color / 2;
// 		write_line(mlx, x, drawStart, drawEnd, color);
// 		x++;
// 	}
// 	return (0);
// }
// 
// void	init_mlx(t_mlx *mlx)
// {
// 	mlx->mlx_ptr = safe_mlx_init();
// 	mlx->win_ptr = safe_mlx_new_window(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "test");
// 	mlx->posX = 3;
// 	mlx->posY = 5;
// 	mlx->dirX = -1;
// 	mlx->dirY = 0;
// 	mlx->planeX = 0;
// 	mlx->planeY = 0.66;
// }
// 
// int	main(void)
// {
// 	t_mlx		mlx;
// 	t_player	player;
// 
// 	mlx.player = &player;
// 	player.x = WINDOW_WIDTH / 2;
// 	player.y = WINDOW_HEIGHT / 2;
// 	player.rotationAngle = M_PI / 2;
// 	init_mlx(&mlx);
// 	//draw_map_and_player(&mlx, &player);
// 
//  	mlx_loop_hook(mlx.mlx_ptr, ray_casting, &mlx);
// 	mlx_hook(mlx.win_ptr, 2, 1L << 0, event_key_press, &mlx);
// 	mlx_hook(mlx.win_ptr, 17, 1L << 2, destroy_mlx, &mlx);
// 	mlx_loop(mlx.mlx_ptr);
// }

#include <stdio.h>
#include <math.h>

#define TILE_SIZE		48
#define MAP_HEIGHT		16
#define MAP_WIDTH		16

#define WINDOW_WIDTH	(MAP_WIDTH * TILE_SIZE)
#define WINDOW_HEIGHT	(MAP_HEIGHT * TILE_SIZE)

#define MINIMAP_SCALE	4
#define MINIMAP_TILE	(TILE_SIZE / MINIMAP_SCALE)
#define MINIMAP_WIDTH	(WINDOW_WIDTH / MINIMAP_SCALE)
#define MINIMAP_HEIGHT	(WINDOW_HEIGHT / MINIMAP_SCALE)

#define PLAYER_SIZE		(TILE_SIZE / 4)

#define SPACE			0
#define WALL			1
#define PLAYER			2

#define COLOR_SPACE		0xFFFFFF
#define COLOR_WALL		0x777777
#define COLOR_PLAYER	0xFF0000

#define NORTH			(M_PI / 2)
#define SOUTH			(3 * M_PI / 2)
#define EAST			(0)
#define WEST			(M_PI)

#define FOV				(60 * (M_PI / 180))

// #define NUM_RAYS WINDOW_WIDTH
// #define FOV_ANGLE (60 * (M_PI / 180))

typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_mlx	t_mlx;

struct s_map
{
	char	**grid;
	size_t	width;
	size_t	height;
};

// fov: field of view
struct s_player
{
	double	x;
	double	y;
	double	direction;
	double	fov;
};

struct s_ray
{
	double	angle;
	double	distance;
	bool	hit_wall;
	bool	hit_vertical;
};

struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_player	player;
	t_ray		ray;
};


int map[MAP_HEIGHT][MAP_WIDTH] = {
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,0,0,2,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
   {1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1},
   {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
   {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	draw_cell(t_mlx *mlx, size_t cell_x, size_t cell_y)
{
	size_t	pixel_x;
	size_t	pixel_y;
	size_t	pixel_x_end;
	size_t	pixel_y_end;
	size_t	pixel_x_start;

	pixel_x = cell_x * MINIMAP_TILE + (WINDOW_WIDTH - MINIMAP_WIDTH);
	pixel_y = cell_y * MINIMAP_TILE + (WINDOW_HEIGHT - MINIMAP_HEIGHT);
	pixel_x_end = pixel_x + MINIMAP_TILE;
	pixel_y_end = pixel_y + MINIMAP_TILE;
	pixel_x_start = pixel_x;
	while (pixel_y < pixel_y_end)
	{
		pixel_x = pixel_x_start;
		while (pixel_x < pixel_x_end)
		{
			if (map[cell_y][cell_x] == WALL)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pixel_x, pixel_y, COLOR_WALL);
			else if (map[cell_y][cell_x] == SPACE)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pixel_x, pixel_y, COLOR_SPACE);
			else if (map[cell_y][cell_x] == PLAYER)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pixel_x, pixel_y, COLOR_PLAYER);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_minimap(t_mlx *mlx)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			draw_cell(mlx, x, y);
			x++;
		}
		y++;
	}
}

void	cast_ray(t_player *player, t_ray *ray)
{
	double	x_intercecpt;
	double	y_intercecpt;
	double	x_step;
	double	y_step;

	ray->hit_wall = false;
	x_intercecpt = player->x + (1 - (player->x - floor(player->x))x_in_cell) * cos(ray->angle);
	y_intercecpt = player->y + (1 - (player->y - floor(player->y))y_in_cell) * sin(ray->angle);
	x_step = cos(ray->angle);
	y_step = sin(ray->angle);
	while (!ray->hit_wall)
	{
	}
}

void	ray_casting(t_mlx *mlx)
{
	size_t	i;

	i = 0;
	while (i < WINDOW_WIDTH)
	{
		mlx->ray.angle = mlx->player.direction - (mlx->player.fov / 2) + ((double)i / WINDOW_WIDTH) * mlx->player.fov;
		cast_ray(&mlx->player, &mlx->ray);
		i++
	}
}

int	draw(void *mlx)
{
	draw_minimap(mlx);
	ray_casting(mlx);
	return (0);
}

// void	init_ray(t_ray *ray)
// {
// 	ray->angle = 
// }

void	init_player(t_player *player)
{
	player->x = 4;
	player->y = 4;
	player->direction = NORTH;
	player->fov = FOV;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx");
//	init_map(mlx);
	init_player(&mlx->player);
//	printf("%lf\n", mlx->player.direction);
//	init_ray(mlx);
}

int	main(void)
{
	t_mlx	mlx;

	init_mlx(&mlx);
  	mlx_loop_hook(mlx.mlx_ptr, draw, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}

