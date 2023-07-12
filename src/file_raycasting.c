/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_raycasting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 22:55:17 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/12 23:29:53 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static void	init_ray(t_player *player, t_ray *ray, t_helper *helper)
{
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	helper->mapX = (int)player->x;
	helper->mapY = (int)player->y;
	helper->deltaDistX = fabs(1 / ray->dir_x);
	helper->deltaDistY = fabs(1 / ray->dir_y);
}

static void	calculate_step_side_dist(t_player *player,
	t_ray *ray, t_helper *helper)
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

static void	perform_dda(t_map *map, t_ray *ray, t_helper *helper)
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

static void	calculate_wall_distance(t_player *player,
	t_ray *ray, t_helper *helper)
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
