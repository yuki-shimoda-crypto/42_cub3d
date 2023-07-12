/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/13 03:39:52 by yshimoda         ###   ########.fr       */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void init_ray(t_player *player, t_ray *ray)
{
    ray->map_x = (int)player->x;
    ray->map_y = (int)player->y;
    ray->dir_x = cos(ray->angle);
    ray->dir_y = sin(ray->angle);
    ray->delta_dist_x = fabs(1 / ray->dir_x);
    ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit_wall = false;
}

static void calculate_step_and_sidedist(t_player *player, t_ray *ray)
{
    if (ray->dir_x < 0)
    {
        ray->step_x = -1;
        ray->side_dist_x = (player->x - ray->map_x) * ray->delta_dist_x;
    }
    else
    {
        ray->step_x = 1;
        ray->side_dist_x = (ray->map_x + 1.0 - player->x) * ray->delta_dist_x;
    }

    if (ray->dir_y < 0)
    {
        ray->step_y = -1;
        ray->side_dist_y = (player->y - ray->map_y) * ray->delta_dist_y;
    }
    else
    {
        ray->step_y = 1;
        ray->side_dist_y = (ray->map_y + 1.0 - player->y) * ray->delta_dist_y;
    }
}

static void find_wall_hit(t_map *map, t_ray *ray)
{
    while (ray->hit_wall == false)
    {
        if (ray->side_dist_x < ray->side_dist_y)
        {
            ray->side_dist_x += ray->delta_dist_x;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_dist_y += ray->delta_dist_y;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        if (map->grid[ray->map_y][ray->map_x] == WALL)
            ray->hit_wall = true;
    }
}

static void calculate_wall_dist(t_player *player, t_ray *ray)
{
    if (ray->side == 0)
        ray->distance = (ray->map_x - player->x + (1 - ray->step_x) / 2) / ray->dir_x;
    else
        ray->distance = (ray->map_y - player->y + (1 - ray->step_y) / 2) / ray->dir_y;
}

void cast_ray(t_map *map, t_player *player, t_ray *ray)
{

    init_ray(player, ray);
    calculate_step_and_sidedist(player, ray);
    find_wall_hit(map, ray);
    calculate_wall_dist(player, ray);
}

void	load_textures(t_mlx *mlx, t_game_data *data)
{
	int i;
	int	x;
	int	y;
	char *texture_files[4];

	texture_files[0] = data->n_texture;
	texture_files[1] = data->s_texture;
	texture_files[2] = data->e_texture;
	texture_files[3] = data->w_texture;
	i = 0;
	while (i < 4)
	{
		mlx->texture[i].img = mlx_xpm_file_to_image(mlx->mlx_ptr, texture_files[i], &x, &y);
		if (mlx->texture[i].img == NULL)
			exit_error("Can not file to mlx image\n", false);
		mlx->texture[i].data = mlx_get_data_addr(mlx->texture[i].img, &mlx->texture[i].bpp, &mlx->texture[i].size_l, &mlx->texture[i].endian);
		i++;
	}
}


void	make_color(t_game_data *data, long *f_color, long *c_color)
{
	data->color_floor = f_color[0] * (16 * 16 * 16 * 16) + f_color[1] * (16 * 16) + f_color[2];
	data->color_ceiling = c_color[0] * (16 * 16 * 16 * 16) + c_color[1] * (16 * 16) + c_color[2];
}

void	draw_wall_strip(t_mlx *mlx, t_ray *ray, size_t x, t_game_data *data)
{
	size_t	y;
	double	corrected_distance;
	double	strip_height;
	double	top_pixel;
	double	bottom_pixel;
	int		color;

	corrected_distance = ray->distance * cos(ray->angle - mlx->player.direction);
	strip_height = WINDOW_HEIGHT * 1 / (corrected_distance);
	top_pixel = ((double)WINDOW_HEIGHT / 2.0) - (strip_height / 2.0);
	bottom_pixel = ((double)WINDOW_HEIGHT / 2.0) + (strip_height / 2.0);
	if (bottom_pixel > WINDOW_HEIGHT)
		bottom_pixel = WINDOW_HEIGHT;

	make_color(data, data->f_color, data->c_color);
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
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, data->color_ceiling);
		}
		else if (y > bottom_pixel)
		{
			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, data->color_floor);
		}
		else
		{


	double wallX; // the exact position where the wall was hit
		if (ray->side == 0) // If its a y-axis wall
			wallX = mlx->player.y + ray->distance * ray->dir_y;
		else // if its an x-axis wall
			wallX = mlx->player.x + ray->distance * ray->dir_x;
		wallX -= floor(wallX); // only keep the fractional part

		// x coordinate on the texture
		int texture_x = (int)(wallX * (double)TILE_SIZE);
		if (ray->side == 0 && ray->dir_x > 0)
			texture_x = TILE_SIZE - texture_x - 1;
		else if (ray->side == 1 && ray->dir_y < 0)
			texture_x = TILE_SIZE - texture_x - 1;
		texture_x = TILE_SIZE - texture_x - 1;

 		int texture_y = (y - top_pixel) * TILE_SIZE / strip_height;

		color = *(int *)(mlx->texture[texture_num].data + (texture_y * mlx->texture[texture_num].size_l + texture_x * (mlx->texture[texture_num].bpp / 8)));




 			mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);
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
		draw_wall_strip(mlx, &mlx->ray, x, mlx->data);
		x++;
	}
}

int	draw(void *mlx)
{
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

void	init_player(char **grid, t_player *player)
{
	size_t	x;
	size_t	y;

	player->fov = FOV;
	y = 0;
	while (grid[y])
	{
		x = 0;
		while (grid[y][x])
		{
			if (is_start(player, grid[y][x], x, y))
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
	if (!map->grid)
		exit_error(NULL, true);
	map_node = head;
	y = 0;
	while (y < map->height)
	{
		map->grid[y] = strdup(map_node->line);
		if (!map->grid[y])
			exit_error(NULL, true);
		map_node = map_node->next;
		y++;
	}
}

void	init_mlx(t_mlx *mlx, t_game_data *data)
{
	mlx->mlx_ptr = safe_mlx_init();
	mlx->win_ptr = safe_mlx_new_window(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx");
	init_map(&mlx->map, data->map_node);
	init_player(mlx->map.grid, &mlx->player);
	load_textures(mlx, data);
	mlx->data = data;
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
