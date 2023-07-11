/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/11 23:23:18 by yshimoda         ###   ########.fr       */
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
// 	exit(exit_success);
// 	return (0);
// }
// 
// int	event_key_press(int key_num, t_mlx *mlx)
// {
// 	if (key_num == key_esc)
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
#include <stdlib.h>
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

#define SPACE			'0'
#define WALL			'1'
#define PLAYER			'2'

// minimap
#define COLOR_SPACE		0xFFFFFF
#define COLOR_WALL		0x777777
#define COLOR_PLAYER	0xFF0000

// cub3d
#define COLOR_SKY		0xFFFFFF
#define COLOR_GROUND	0x000000
#define COLOR_NORTH		0x111111
#define COLOR_SOUTH		0x333333
#define COLOR_EAST		0x555555
#define COLOR_WEST		0x777777
#define COLOR_RAY		0x0000FF

#define NORTH			(270 * (M_PI / 180))
#define SOUTH			(90 * (M_PI / 180))
#define EAST			(0 * (M_PI / 180))
#define WEST			(180 * (M_PI / 180))

#define FOV				(60 * (M_PI / 180))

#define MOVE_SPEED		0.1

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
	int		side;
	double	dir_x;
	double	dir_y;
	int		step_x;
	int		step_y;
};

struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_player	player;
	t_ray		ray;
};

void	draw_cell(t_mlx *mlx, t_map *map, size_t cell_x, size_t cell_y)
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
			if (map->grid[cell_y][cell_x] == WALL)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pixel_x, pixel_y, COLOR_WALL);
			else if (map->grid[cell_y][cell_x] == SPACE)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pixel_x, pixel_y, COLOR_SPACE);
			else if (map->grid[cell_y][cell_x] == PLAYER)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pixel_x, pixel_y, COLOR_PLAYER);
			pixel_x++;
		}
		pixel_y++;
	}
}

void	draw_minimap(t_mlx *mlx, t_map *map)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			draw_cell(mlx, map, x, y);
			x++;
		}
		y++;
	}
}

void cast_ray(t_map *map, t_player *player, t_ray *ray)
{
    int mapX = (int)player->x;
    int mapY = (int)player->y;

    ray->dir_x = cos(ray->angle);
    ray->dir_y = sin(ray->angle);

    double sideDistX;
    double sideDistY;

    double deltaDistX = fabs(1 / ray->dir_x);
    double deltaDistY = fabs(1 / ray->dir_y);
    double perpWallDist;

    ray->hit_wall = false;

    if (ray->dir_x < 0)
	{
        ray->step_x = -1;
        sideDistX = (player->x - mapX) * deltaDistX;
    }
	else
	{
        ray->step_x = 1;
        sideDistX = (mapX + 1.0 - player->x) * deltaDistX;
    }
    if (ray->dir_y < 0)
	{
        ray->step_y = -1;
        sideDistY = (player->y - mapY) * deltaDistY;
    }
	else
	{
        ray->step_y = 1;
        sideDistY = (mapY + 1.0 - player->y) * deltaDistY;
    }
    while (ray->hit_wall == false)
	{
        if (sideDistX < sideDistY)
		{
            sideDistX += deltaDistX;
            mapX += ray->step_x;
            ray->side = 0;
        }
		else
		{
            sideDistY += deltaDistY;
            mapY += ray->step_y;
            ray->side = 1;
        }
        if (map->grid[mapY][mapX] == WALL)
			ray->hit_wall = true;
    }

     if (ray->side == 0)
	 	perpWallDist = (mapX - player->x + (1 - ray->step_x) / 2) / ray->dir_x;
     else
	 	perpWallDist = (mapY - player->y + (1 - ray->step_y) / 2) / ray->dir_y;

    ray->distance = perpWallDist;
}

void	draw_wall_strip(t_mlx *mlx, t_player *player, t_ray *ray, size_t x)
{
	size_t	y;
	double	corrected_distance;
	double	strip_height;
	double	top_pixel;
	double	bottom_pixel;

	corrected_distance = ray->distance * cos(ray->angle - player->direction);
//	corrected_distance = fabs(ray->distance * cos(ray->angle - player->direction));
//	corrected_distance = ray->distance * cos(ray->angle - player->direction);
	printf("x = %zu, distance = %lf\n", x, corrected_distance);
//	printf("ray_distance\t%lf\n", ray->distance);
//	printf("corrected_distance\t%lf\n", corrected_distance);
	strip_height = WINDOW_HEIGHT * 1 / (corrected_distance);
//	printf("WINDOW_HEIGHT%d\tstrip_height\t%lf\n", WINDOW_HEIGHT, strip_height);
	top_pixel = ((double)WINDOW_HEIGHT / 2.0) - (strip_height / 2.0);
//	printf("top_pixel%lf\n", top_pixel);
	bottom_pixel = ((double)WINDOW_HEIGHT / 2.0) + (strip_height / 2.0);
	if (top_pixel < 0)
		top_pixel = 0;
	if (bottom_pixel > WINDOW_HEIGHT)
		bottom_pixel = WINDOW_HEIGHT;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < top_pixel)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, COLOR_SKY);
		}
		else if (y > bottom_pixel)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, COLOR_GROUND);
		}
		else
		{
			if (ray->side && ray->dir_y < 0)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, (COLOR_NORTH));
			else if (ray->side && ray->dir_y >= 0)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, (COLOR_SOUTH));
			else if (!ray->side && ray->dir_x > 0)
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, COLOR_EAST);
			else
				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, (COLOR_WEST));
		}
		y++;
	}
}

void	ray_casting(t_mlx *mlx)
{
	size_t	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		mlx->ray.angle = mlx->player.direction - (mlx->player.fov / 2) + ((double)x / (double)WINDOW_WIDTH) * mlx->player.fov;
		if (mlx->ray.angle < 0)
			mlx->ray.angle += 2 * M_PI;
		else if (mlx->ray.angle > 2 * M_PI)
			mlx->ray.angle -= 2 * M_PI;
		printf("%lf\n", mlx->ray.angle * 180 / M_PI);
		cast_ray(&mlx->map, &mlx->player, &mlx->ray);
		draw_wall_strip(mlx, &mlx->player, &mlx->ray, x);
		x++;
	}
}

int	draw(void *mlx)
{
	draw_minimap(mlx, &((t_mlx *)mlx)->map);
	ray_casting(mlx);
	return (0);
}

void	init_map(t_map *map, t_player *player)
{
	size_t	x;
	size_t	y;

	map->grid = calloc(sizeof(char *), MAP_HEIGHT + 1);
	y = 0;
	while (y < MAP_HEIGHT)
	{
		map->grid[y] = calloc(sizeof(char), MAP_WIDTH + 1);
		y++;
	}
	y = 0;
	while (y < MAP_HEIGHT)
	{
		x = 0;
		while (x < MAP_WIDTH)
		{
			if (y == 0 || x == 0 || x == MAP_HEIGHT - 1 || y == MAP_WIDTH - 1)
				map->grid[y][x] = '1';
			else
				map->grid[y][x] = '0';
			x++;
		}
		y++;
	}
	map->grid[3][3] = '1';
	map->grid[(size_t)(player->y)][(size_t)(player->x)] = '2';
}

void	init_player(t_player *player)
{
	player->x = 4.3;
	player->y = 4.3;
	player->direction = NORTH;
	player->fov = FOV;
}

void	printf_map(char **grid)
{
	size_t	y;

	y = 0;
	while (y < MAP_HEIGHT)
	{
		printf("%s\n", grid[y]);
		y++;
	}
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx");
	init_player(&mlx->player);
	init_map(&mlx->map, &mlx->player);
	printf_map(mlx->map.grid);
//	init_ray(mlx);
}

int	destroy_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

void	change_move_value(t_map *map, t_player *player, double new_x, double new_y)
{
	map->grid[(size_t)(player->y)][(size_t)(player->x)] = '0';
	map->grid[(size_t)(new_y)][(size_t)(new_x)] = '2';
	player->x = new_x;
	player->y = new_y;
}

int	event_key_press(int key_num, t_mlx *mlx)
{
	double	new_x;
	double	new_y;

	if (key_num == KEY_ESC)
		destroy_mlx(mlx);
	else if (key_num == KEY_W)
	{
		new_x = mlx->player.x + MOVE_SPEED * cos(mlx->player.direction);
		new_y = mlx->player.y + MOVE_SPEED * sin(mlx->player.direction);
		if (mlx->map.grid[(int)new_y][(int)new_x] != WALL)
			change_move_value(&mlx->map, &mlx->player, new_x, new_y);
	}
	else if (key_num == KEY_S)
	{
		new_x = mlx->player.x - MOVE_SPEED * cos(mlx->player.direction);
		new_y = mlx->player.y - MOVE_SPEED * sin(mlx->player.direction);
		if (mlx->map.grid[(int)new_y][(int)new_x] != WALL)
			change_move_value(&mlx->map, &mlx->player, new_x, new_y);
	}
	else if (key_num == KEY_A)
	{
		new_x = mlx->player.x + MOVE_SPEED * sin(mlx->player.direction);
		new_y = mlx->player.y - MOVE_SPEED * cos(mlx->player.direction);
		if (mlx->map.grid[(int)new_y][(int)new_x] != WALL)
			change_move_value(&mlx->map, &mlx->player, new_x, new_y);
	}
	else if (key_num == KEY_D)
	{
		new_x = mlx->player.x - MOVE_SPEED * sin(mlx->player.direction);
		new_y = mlx->player.y + MOVE_SPEED * cos(mlx->player.direction);
		if (mlx->map.grid[(int)new_y][(int)new_x] != WALL)
			change_move_value(&mlx->map, &mlx->player, new_x, new_y);
	}
	else if (key_num == KEY_LEFT)
	{
		mlx->player.direction -= 10 * (M_PI / 180);
		if (mlx->player.direction < 0)
			mlx->player.direction += 2 * M_PI;
	}
	else if (key_num == KEY_RIGHT)
	{
		mlx->player.direction += 10 * (M_PI / 180);
		if (mlx->player.direction > 2 * M_PI)
			mlx->player.direction -= 2 * M_PI;
	}
	return (9);
}

int	main(void)
{
	t_mlx	mlx;

	init_mlx(&mlx);
  	mlx_loop_hook(mlx.mlx_ptr, draw, &mlx);
 	mlx_hook(mlx.win_ptr, 2, 1L << 0, event_key_press, &mlx);
 	mlx_hook(mlx.win_ptr, 17, 1L << 2, destroy_mlx, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}

