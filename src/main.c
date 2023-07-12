/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/12 19:21:16 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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


void	load_textures(t_mlx *mlx)
{
	int i;
	int	x;
	int	y;

	char *texture_files[4] = {"texture/north_texture.xpm", "texture/south_texture.xpm", "texture/east_texture.xpm", "texture/west_texture.xpm"};
	for (i = 0; i < 4; i++)
	{
		mlx->texture[i].img = mlx_xpm_file_to_image(mlx->mlx_ptr, texture_files[i], &x, &y);
		if (mlx->texture[i].img == NULL)
			exit(1);
		mlx->texture[i].data = mlx_get_data_addr(mlx->texture[i].img, &mlx->texture[i].bpp, &mlx->texture[i].size_l, &mlx->texture[i].endian);
	}
}
void	draw_wall_strip(t_mlx *mlx, t_player *player, t_ray *ray, size_t x)
{
	size_t	y;
	double	corrected_distance;
	double	strip_height;
	double	top_pixel;
	double	bottom_pixel;

	corrected_distance = ray->distance * cos(ray->angle - player->direction);
	strip_height = WINDOW_HEIGHT * 1 / (corrected_distance);
	top_pixel = ((double)WINDOW_HEIGHT / 2.0) - (strip_height / 2.0);
	bottom_pixel = ((double)WINDOW_HEIGHT / 2.0) + (strip_height / 2.0);
	if (top_pixel < 0)
		top_pixel = 0;
	if (bottom_pixel > WINDOW_HEIGHT)
		bottom_pixel = WINDOW_HEIGHT;

	int texture_num;

	if (ray->side && ray->dir_y < 0)
		texture_num = 0;
	else if (ray->side && ray->dir_y >= 0)
		texture_num = 1;
	else if (!ray->side && ray->dir_x > 0)
		texture_num = 2;
	else
		texture_num = 3;

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
//  			int texture_y = (y - top_pixel) * TILE_SIZE / strip_height;
//  			int color = *(int*)(mlx->texture[texture_num].data + (texture_y * mlx->texture[texture_num].size_l));
//  			int bytes_per_pixel = mlx->texture[texture_num].bpp / 8; // calculate bytes per pixel
//  			color = *(int*)(mlx->texture[texture_num].data + (texture_y * mlx->texture[texture_num].size_l * bytes_per_pixel));
//  			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);
//  			int x, y;

// int texX;
// if (ray->side == 0) // Y-side
//     texX = (int)(player->y + ray->distance * ray->dir_y) % TILE_SIZE;
// else // X-side
//     texX = (int)(player->x + ray->distance * ray->dir_x) % TILE_SIZE;
// 
//

  double wallX; // the exact position where the wall was hit
    if (ray->side == 0) // If its a y-axis wall
        wallX = player->y + ray->distance * ray->dir_y;
    else // if its an x-axis wall
        wallX = player->x + ray->distance * ray->dir_x;
    wallX -= floor(wallX); // only keep the fractional part

    // x coordinate on the texture
    int texture_x = (int)(wallX * (double)TILE_SIZE);
    if (ray->side == 0 && ray->dir_x > 0)
        texture_x = TILE_SIZE - texture_x - 1;
	else if (ray->side == 1 && ray->dir_y < 0)
        texture_x = TILE_SIZE - texture_x - 1;
     texture_x = TILE_SIZE - texture_x - 1;

 		int texture_y = (y - top_pixel) * TILE_SIZE / strip_height;

int color = *(int *)(mlx->texture[texture_num].data + (texture_y * mlx->texture[texture_num].size_l + texture_x * (mlx->texture[texture_num].bpp / 8)));

//int color = *(int *)(mlx->texture[texture_num].data + (texture_y * mlx->texture[texture_num].size_l + texX * (mlx->texture[texture_num].bpp / 8)));

//color = *(int *)(mlx->texture[texture_num].data + (texture_y * mlx->texture[texture_num].size_l + x * TILE_SIZE/ (size_t)strip_height * (mlx->texture[texture_num].bpp / 8)));
//color = *(int *)(mlx->texture[texture_num].data + (texture_y * mlx->texture[texture_num].size_l + x * (mlx->texture[texture_num].bpp / 8) % (size_t)strip_height));


//  			int texture_y = (y - top_pixel) * TILE_SIZE / strip_height;
//  			int color = *(int*)(mlx->texture[texture_num].data + (texture_y * mlx->texture[texture_num].size_l));
 			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);

// 			if (ray->side && ray->dir_y < 0)
// //				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, (COLOR_NORTH));
// 				mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->texture_north, x, y);
// 			else if (ray->side && ray->dir_y >= 0)
// 				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, (COLOR_SOUTH));
// 			else if (!ray->side && ray->dir_x > 0)
// 				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, COLOR_EAST);
// 			else
// 				mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, (COLOR_WEST));
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
		cast_ray(&mlx->map, &mlx->player, &mlx->ray);
		draw_wall_strip(mlx, &mlx->player, &mlx->ray, x);
		x++;
	}
}

int	draw(void *mlx)
{
//	draw_minimap(mlx, &((t_mlx *)mlx)->map);
	ray_casting(mlx);
	return (0);
}

bool	is_start(t_player *player, char c, size_t x, size_t y)
{
	if (c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (false);
	if (c == 'N')
		player->direction = NORTH;
	else if (c == 'S')
		player->direction = SOUTH;
	else if (c == 'E')
		player->direction = EAST;
	else if (c == 'W')
		player->direction = WEST;
	player->x = x;
	player->y = y;
	return (true);
}

void	init_player(t_map *map, t_player *player)
{
	size_t	x;
	size_t	y;

	player->fov = FOV;
	y = 0;
	while (map->grid[y])
	{
		x = 0;
		while (map->grid[y][x])
		{
			if (is_start(player, map->grid[y][x], x, y))
				return ;
			x++;
		}
		y++;
	}
}

void	printf_map(t_map *map)
{
	size_t	y;

	y = 0;
	while (y < map->height)
	{
		printf("%s\n", map->grid[y]);
		y++;
	}
}

void	init_map(t_map *map, t_map_node *map_node)
{
	t_map_node	*head;
	size_t		y;

	head = map_node;
	map->height = 0;
	while (map_node)
	{
		map->height += 1;
		map_node = map_node->next;
	}
	map->grid = calloc(sizeof(char *), map->height + 1);
	map_node = head;
	y = 0;
	while (y < map->height)
	{
		map->grid[y] = strdup(map_node->line);
		map_node = map_node->next;
		y++;
	}
}

void	init_mlx(t_mlx *mlx, t_game_data *data)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx");
	init_map(&mlx->map, data->map_node);
	init_player(&mlx->map, &mlx->player);
	load_textures(mlx);
//	init_ray(mlx);
//	printf_map(&mlx->map);
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


static void handle_escape_key(t_mlx *mlx)
{
	destroy_mlx(mlx);
}

static void handle_move_key(int key_num, t_mlx *mlx)
{
	double	new_x;
	double	new_y;

	if (key_num == KEY_W)
	{
		new_x = mlx->player.x + MOVE_SPEED * cos(mlx->player.direction);
		new_y = mlx->player.y + MOVE_SPEED * sin(mlx->player.direction);
	}
	else if (key_num == KEY_S)
	{
		new_x = mlx->player.x - MOVE_SPEED * cos(mlx->player.direction);
		new_y = mlx->player.y - MOVE_SPEED * sin(mlx->player.direction);
	}
	else if (key_num == KEY_A)
	{
		new_x = mlx->player.x + MOVE_SPEED * sin(mlx->player.direction);
		new_y = mlx->player.y - MOVE_SPEED * cos(mlx->player.direction);
	}
	else // KEY_D
	{
		new_x = mlx->player.x - MOVE_SPEED * sin(mlx->player.direction);
		new_y = mlx->player.y + MOVE_SPEED * cos(mlx->player.direction);
	}

	if (mlx->map.grid[(int)new_y][(int)new_x] != WALL)
		change_move_value(&mlx->map, &mlx->player, new_x, new_y);
}

static void handle_rotate_key(int key_num, t_mlx *mlx)
{
	if (key_num == KEY_LEFT)
	{
		mlx->player.direction -= 10 * (M_PI / 180);
		if (mlx->player.direction < 0)
			mlx->player.direction += 2 * M_PI;
	}
	else // KEY_RIGHT
	{
		mlx->player.direction += 10 * (M_PI / 180);
		if (mlx->player.direction > 2 * M_PI)
			mlx->player.direction -= 2 * M_PI;
	}
}

int	event_key_press(int key_num, t_mlx *mlx)
{
	if (key_num == KEY_ESC)
		handle_escape_key(mlx);
	else if (key_num == KEY_W || key_num == KEY_S || key_num == KEY_A || key_num == KEY_D)
		handle_move_key(key_num, mlx);
	else if (key_num == KEY_LEFT || key_num == KEY_RIGHT)
		handle_rotate_key(key_num, mlx);
	return (0);
}

void	mlx_func(t_game_data *data)
{
	t_mlx	mlx;

	init_mlx(&mlx, data);
  	mlx_loop_hook(mlx.mlx_ptr, draw, &mlx);
 	mlx_hook(mlx.win_ptr, 2, 1L << 0, event_key_press, &mlx);
 	mlx_hook(mlx.win_ptr, 17, 1L << 2, destroy_mlx, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

static void	init_game_data(t_game_data *data)
{
	data->map_node = NULL;
	data->n_texture = NULL;
	data->s_texture = NULL;
	data->w_texture = NULL;
	data->e_texture = NULL;
	data->f_color[0] = 0;
	data->f_color[1] = 0;
	data->f_color[2] = 0;
	data->c_color[0] = 0;
	data->c_color[1] = 0;
	data->c_color[2] = 0;
}

int	main(int argc, const char *argv[])
{
	t_cub_file_node		*cub_file_node;
	t_game_data			data;

	init_game_data(&data);
	check_file_name(argc, argv);
	cub_file_node = read_cub_file(argv[1]);
	check_cub_file(cub_file_node, &data);
	mlx_func(&data);
	free_cub_file_node(cub_file_node);
	free_data(&data);
	return (0);
}
