/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_initialization.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 05:56:38 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/13 06:36:11 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include "cub3d.h"

static void	init_ray(t_player *player, t_ray *ray)
{
	ray->map_x = (int)player->x;
	ray->map_y = (int)player->y;
	ray->dir_x = cos(ray->angle);
	ray->dir_y = sin(ray->angle);
	if (ray->dir_x == 0)
		ray->delta_dist_x = DBL_MAX;
	else
		ray->delta_dist_x = fabs(1 / ray->dir_x);
	if (ray->dir_y == 0)
		ray->delta_dist_y = DBL_MAX;
	else
		ray->delta_dist_y = fabs(1 / ray->dir_y);
	ray->hit_wall = false;
}

static void	calculate_step_and_sidedist(t_player *player, t_ray *ray)
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

static void	find_wall_hit(t_map *map, t_ray *ray)
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

static void	calculate_wall_dist(t_player *player, t_ray *ray)
{
	if (ray->side == 0)
		ray->distance = (ray->map_x - player->x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->distance = (ray->map_y - player->y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
}

void	cast_ray(t_map *map, t_player *player, t_ray *ray)
{
	init_ray(player, ray);
	calculate_step_and_sidedist(player, ray);
	find_wall_hit(map, ray);
	calculate_wall_dist(player, ray);
}
