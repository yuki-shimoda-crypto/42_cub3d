/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:22:18 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/13 06:32:28 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cub3d.h"

static void	init_drawing(t_ray *ray, t_mlx *mlx, t_draw *draw)
{
	draw->corrected_distance
		= ray->distance * cos(ray->angle - mlx->player.direction);
	if (draw->corrected_distance == 0)
		draw->corrected_distance = 0.2;
	draw->strip_height = WINDOW_HEIGHT * 1 / (draw->corrected_distance);
	draw->top_pixel = ((double)WINDOW_HEIGHT / 2.0)
		- (draw->strip_height / 2.0);
	draw->bottom_pixel = ((double)WINDOW_HEIGHT / 2.0)
		+ (draw->strip_height / 2.0);
	if (draw->bottom_pixel > WINDOW_HEIGHT)
		draw->bottom_pixel = WINDOW_HEIGHT;
}

static void	determine_texture_number(t_ray *ray, t_draw *draw)
{
	if (ray->side && ray->dir_y < 0)
		draw->texture_num = 0;
	else if (ray->side && ray->dir_y >= 0)
		draw->texture_num = 1;
	else if (!ray->side && ray->dir_x > 0)
		draw->texture_num = 2;
	else
		draw->texture_num = 3;
}

static void	draw_wall(t_mlx *mlx, size_t x, size_t y, t_draw *draw)
{
	double	wall_x;
	int		texture_y;
	int		color;
	int		texture_x;

	if (mlx->ray.side == 0)
		wall_x = mlx->player.y + mlx->ray.distance * mlx->ray.dir_y;
	else
		wall_x = mlx->player.x + mlx->ray.distance * mlx->ray.dir_x;
	wall_x -= floor(wall_x);
	texture_x = (int)(wall_x * (double)TILE_SIZE);
	if (mlx->ray.side == 0 && mlx->ray.dir_x > 0)
		texture_x = TILE_SIZE - texture_x - 1;
	if (mlx->ray.side == 1 && mlx->ray.dir_y < 0)
		texture_x = TILE_SIZE - texture_x - 1;
	texture_x = TILE_SIZE - texture_x - 1;
	texture_y = (y - draw->top_pixel) * TILE_SIZE / draw->strip_height;
	color = *(int *)(mlx->texture[draw->texture_num].data + (texture_y
				* mlx->texture[draw->texture_num].size_l
				+ texture_x * (mlx->texture[draw->texture_num].bpp / 8)));
	mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);
}

static void	draw_ceiling_and_floor(t_mlx *mlx, t_draw *draw, size_t x, size_t y)
{
	if (y < draw->top_pixel)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr,
			x, y, mlx->data->color_ceiling);
	}
	else if (y > draw->bottom_pixel)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, mlx->data->color_floor);
	}
}

void	draw_wall_strip(t_mlx *mlx, t_ray *ray, size_t x, t_game_data *data)
{
	size_t	y;
	t_draw	draw;

	init_drawing(ray, mlx, &draw);
	make_color(data, data->f_color, data->c_color);
	determine_texture_number(ray, &draw);
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		if (y >= draw.top_pixel && y <= draw.bottom_pixel)
		{
			draw_wall(mlx, x, y, &draw);
		}
		else
		{
			draw_ceiling_and_floor(mlx, &draw, x, y);
		}
		y++;
	}
}
