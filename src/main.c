/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/12 18:50:40 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void	update_pixels(size_t *pixel_x, size_t *pixel_y,
						size_t cell_x, size_t cell_y)
{
	*pixel_x = cell_x * MINIMAP_TILE + (WINDOW_WIDTH - MINIMAP_WIDTH);
	*pixel_y = cell_y * MINIMAP_TILE + (WINDOW_HEIGHT - MINIMAP_HEIGHT);
}

void	set_pixel_color(t_mlx *mlx,
						size_t pixel_x, size_t pixel_y, char cell_type)
{
	if (cell_type == WALL)
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, pixel_x, pixel_y, COLOR_WALL);
	else if (cell_type == SPACE)
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr,
			pixel_x, pixel_y, COLOR_SPACE);
	else if (cell_type == PLAYER)
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr,
			pixel_x, pixel_y, COLOR_PLAYER);
}

void	draw_cell(t_mlx *mlx, t_map *map, size_t cell_x, size_t cell_y)
{
	size_t	pixel_x;
	size_t	pixel_y;
	char	cell_type;
	size_t	temp_pixel_x;

	cell_type = map->grid[cell_y][cell_x];
	update_pixels(&pixel_x, &pixel_y, cell_x, cell_y);
	while (pixel_y < pixel_y + MINIMAP_TILE)
	{
		temp_pixel_x = pixel_x;
		while (temp_pixel_x < pixel_x + MINIMAP_TILE)
		{
			set_pixel_color(mlx, temp_pixel_x, pixel_y, cell_type);
			temp_pixel_x++;
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

void	init_ray(t_player *player, t_ray *ray, t_helper *helper)
{
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	helper->mapX = (int)player->x;
	helper->mapY = (int)player->y;
	helper->deltaDistX = fabs(1 / ray->dir_x);
	helper->deltaDistY = fabs(1 / ray->dir_y);
}

void	calculate_step_side_dist(t_player *player, t_ray *ray, t_helper *helper)
{
	if (ray->dir_x < 0)
	{
		ray->step_x = -1;
		helper->sideDistX = (player->x - helper->mapX) * helper->deltaDistX;
	}
	else
	{
		ray->step_x = 1;
		helper->sideDistX = (helper->mapX + 1.0 - player->x)
			* helper->deltaDistX;
	}
	if (ray->dir_y < 0)
	{
		ray->step_y = -1;
		helper->sideDistY = (player->y - helper->mapY) * helper->deltaDistY;
	}
	else
	{
		ray->step_y = 1;
		helper->sideDistY = (helper->mapY + 1.0 - player->y)
			* helper->deltaDistY;
	}
}

void	perform_dda(t_map *map, t_ray *ray, t_helper *helper)
{
	while (ray->hit_wall == false)
	{
		if (helper->sideDistX < helper->sideDistY)
		{
			helper->sideDistX += helper->deltaDistX;
			helper->mapX += ray->step_x;
			ray->side = 0;
		}
		else
		{
			helper->sideDistY += helper->deltaDistY;
			helper->mapY += ray->step_y;
			ray->side = 1;
		}
		if (map->grid[helper->mapY][helper->mapX] == WALL)
			ray->hit_wall = true;
	}
}

void	calculate_wall_distance(t_player *player, t_ray *ray, t_helper *helper)
{
	double	perpWallDist;

	if (ray->side == 0)
		perpWallDist = (helper->mapX - player->x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		perpWallDist = (helper->mapY - player->y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
	ray->distance = perpWallDist;
}

void	cast_ray(t_map *map, t_player *player, t_ray *ray)
{
	t_helper	helper;

	init_ray(player, ray, &helper);
	ray->hit_wall = false;
	calculate_step_side_dist(player, ray, &helper);
	perform_dda(map, ray, &helper);
	calculate_wall_distance(player, ray, &helper);
}

void	load_textures(t_mlx *mlx)
{
	int		i;
	int		x;
	int		y;
	char	*texture_files[4];

	texture_files[0] = "texture/north_texture.xpm";
	texture_files[1] = "texture/south_texture.xpm";
	texture_files[2] = "texture/east_texture.xpm";
	texture_files[3] = "texture/west_texture.xpm";
	i = 0;
	while (i < 4)
	{
		mlx->texture[i].img = mlx_xpm_file_to_image(mlx->mlx_ptr, texture_files[i], &x, &y);
		if (mlx->texture[i].img == NULL)
			exit(1);
		mlx->texture[i].data = mlx_get_data_addr(mlx->texture[i].img, &mlx->texture[i].bpp, &mlx->texture[i].size_l, &mlx->texture[i].endian);
		i++;
	}
}

void calc_wall(t_wall *wall, t_player *player, t_ray *ray)
{
	double corrected_distance;

	corrected_distance = ray->distance * cos(ray->angle - player->direction);
	wall->strip_height = WINDOW_HEIGHT * 1 / corrected_distance;
	wall->top_pixel = ((double)WINDOW_HEIGHT / 2.0) - (wall->strip_height / 2.0);
	wall->bottom_pixel = ((double)WINDOW_HEIGHT / 2.0) + (wall->strip_height / 2.0);

	if (wall->top_pixel < 0)
		wall->top_pixel = 0;
	if (wall->bottom_pixel > WINDOW_HEIGHT)
		wall->bottom_pixel = WINDOW_HEIGHT;
}

void set_texture_num(t_wall *wall, t_ray *ray)
{
	if (ray->side && ray->dir_y < 0)
		wall->texture_num = 0;
	else if (ray->side && ray->dir_y >= 0)
		wall->texture_num = 1;
	else if (!ray->side && ray->dir_x > 0)
		wall->texture_num = 2;
	else
		wall->texture_num = 3;
}

void texture_mapping(t_mlx *mlx, t_wall *wall, t_player *player, t_ray *ray, size_t x, size_t y)
{
	double wallX;
	int texture_x, texture_y, color;

	if (ray->side == 0)
		wallX = player->y + ray->distance * ray->dir_y;
	else
		wallX = player->x + ray->distance * ray->dir_x;
	wallX -= floor(wallX);

	texture_x = (int)(wallX * (double)TILE_SIZE);
	if (ray->side == 0 && ray->dir_x > 0)
		texture_x = TILE_SIZE - texture_x - 1;
	if (ray->side == 1 && ray->dir_y < 0)
		texture_x = TILE_SIZE - texture_x - 1;

	texture_y = (y - wall->top_pixel) * TILE_SIZE / wall->strip_height;

	color = *(int *)(mlx->texture[wall->texture_num].data + (texture_y * mlx->texture[wall->texture_num].size_l + texture_x * (mlx->texture[wall->texture_num].bpp / 8)));

	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);
}

void draw_wall_strip(t_mlx *mlx, t_player *player, t_ray *ray, size_t x)
{
	t_wall wall;
	size_t y;

	calc_wall(&wall, player, ray);
	set_texture_num(&wall, ray);

	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y < wall.top_pixel)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, COLOR_SKY);
		}
		else if (y > wall.bottom_pixel)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, COLOR_GROUND);
		}
		else
		{
			texture_mapping(mlx, &wall, player, ray, x, y);
		}
		y++;
	}
}//

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
	load_textures(mlx);
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
