/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_minimap.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:46:32 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/12 22:46:42 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
