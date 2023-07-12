/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_movement.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:24:54 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/12 23:26:32 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	change_move_value(t_map *map, t_player *player,
	double new_x, double new_y)
{
	map->grid[(size_t)(player->y)][(size_t)(player->x)] = '0';
	map->grid[(size_t)(new_y)][(size_t)(new_x)] = '2';
	player->x = new_x;
	player->y = new_y;
}

void	handle_escape_key(t_mlx *mlx)
{
	destroy_mlx(mlx);
}

void	calculate_new_position(int key_num, t_mlx *mlx,
	double *new_x, double *new_y)
{
	if (key_num == KEY_W)
	{
		*new_x = mlx->player.x + MOVE_SPEED * cos(mlx->player.direction);
		*new_y = mlx->player.y + MOVE_SPEED * sin(mlx->player.direction);
	}
	else if (key_num == KEY_S)
	{
		*new_x = mlx->player.x - MOVE_SPEED * cos(mlx->player.direction);
		*new_y = mlx->player.y - MOVE_SPEED * sin(mlx->player.direction);
	}
	else if (key_num == KEY_A)
	{
		*new_x = mlx->player.x + MOVE_SPEED * sin(mlx->player.direction);
		*new_y = mlx->player.y - MOVE_SPEED * cos(mlx->player.direction);
	}
	else
	{
		*new_x = mlx->player.x - MOVE_SPEED * sin(mlx->player.direction);
		*new_y = mlx->player.y + MOVE_SPEED * cos(mlx->player.direction);
	}
}

void	handle_move_key(int key_num, t_mlx *mlx)
{
	double	new_x;
	double	new_y;

	calculate_new_position(key_num, mlx, &new_x, &new_y);
	if (mlx->map.grid[(int)new_y][(int)new_x] != WALL)
		change_move_value(&mlx->map, &mlx->player, new_x, new_y);
}

void	handle_rotate_key(int key_num, t_mlx *mlx)
{
	if (key_num == KEY_LEFT)
	{
		mlx->player.direction -= 10 * (M_PI / 180);
		if (mlx->player.direction < 0)
			mlx->player.direction += 2 * M_PI;
	}
	else
	{
		mlx->player.direction += 10 * (M_PI / 180);
		if (mlx->player.direction > 2 * M_PI)
			mlx->player.direction -= 2 * M_PI;
	}
}
