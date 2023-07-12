/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:27:25 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/13 06:34:31 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cub3d.h"

static bool	is_start(t_player *player, char c, size_t x, size_t y)
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

void	change_move_value(t_map *map, t_player *player,
			double new_x, double new_y)
{
	map->grid[(size_t)(player->y)][(size_t)(player->x)] = '0';
	map->grid[(size_t)(new_y)][(size_t)(new_x)] = '2';
	player->x = new_x;
	player->y = new_y;
}
