/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:13:28 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/12 23:29:15 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	allocate_map(t_map *map)
{
	size_t	y;

	y = 0;
	map->grid = calloc(sizeof(char *), MAP_HEIGHT + 1);
	while (y < MAP_HEIGHT)
	{
		map->grid[y] = calloc(sizeof(char), MAP_WIDTH + 1);
		y++;
	}
}

void	draw_map_boundaries(t_map *map)
{
	size_t	x;
	size_t	y;

	x = 0;
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
}

void	place_wall_and_player(t_map *map, t_player *player)
{
	map->grid[3][3] = '1';
	map->grid[(size_t)(player->y)][(size_t)(player->x)] = '2';
}

void	init_map(t_map *map, t_player *player)
{
	allocate_map(map);
	draw_map_boundaries(map);
	place_wall_and_player(map, player);
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
