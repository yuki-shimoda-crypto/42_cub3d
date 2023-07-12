/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:03:42 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/12 23:30:07 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
		mlx->texture[i].img
			= mlx_xpm_file_to_image(mlx->mlx_ptr, texture_files[i], &x, &y);
		if (mlx->texture[i].img == NULL)
			exit(1);
		mlx->texture[i].data = mlx_get_data_addr(mlx->texture[i].img,
				&mlx->texture[i].bpp, &mlx->texture[i].size_l,
				&mlx->texture[i].endian);
		i++;
	}
}

void	calc_wall_strip(t_draw *draw, t_player *player, t_ray *ray)
{
	double	corrected_distance;
	double	strip_height;

	corrected_distance = ray->distance * cos(ray->angle - player->direction);
	strip_height = WINDOW_HEIGHT * 1 / (corrected_distance);
	draw->top_pixel = ((double)WINDOW_HEIGHT / 2.0) - (strip_height / 2.0);
	draw->bottom_pixel = ((double)WINDOW_HEIGHT / 2.0) + (strip_height / 2.0);
	if (draw->top_pixel < 0)
		draw->top_pixel = 0;
	if (draw->bottom_pixel > WINDOW_HEIGHT)
		draw->bottom_pixel = WINDOW_HEIGHT;
}

void	determine_texture(t_draw *draw, t_ray *ray)
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

void	color_pixel(t_mlx *mlx, t_draw *draw, size_t x, size_t y)
{
	int	color;

	if (y < draw->top_pixel)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, COLOR_SKY);
	}
	else if (y > draw->bottom_pixel)
	{
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, COLOR_GROUND);
	}
	else
	{
		color = *(int *)(mlx->texture[draw->texture_num].data
				+ (int)((y - draw->top_pixel) * TILE_SIZE
					/ (draw->bottom_pixel - draw->top_pixel))
				*mlx->texture[draw->texture_num].size_l
				+ (int)(draw->wallX * (double)TILE_SIZE)
				*(mlx->texture[draw->texture_num].bpp / 8));
		mlx_pixel_put(mlx->mlx_ptr, mlx->win_ptr, x, y, color);
	}
}

void	calc_texture_coords(t_draw *draw, t_player *player, t_ray *ray)
{
	if (ray->side == 0)
		draw->wallX = player->y + ray->distance * ray->dir_y;
	else
		draw->wallX = player->x + ray->distance * ray->dir_x;
	draw->wallX -= floor(draw->wallX);
	if ((ray->side == 0 && ray->dir_x > 0)
		|| (ray->side == 1 && ray->dir_y < 0))
		draw->wallX = TILE_SIZE - draw->wallX - 1;
}
