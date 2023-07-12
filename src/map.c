/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:15:08 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/13 06:15:36 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "cub3d.h"
#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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
	map->grid = ft_calloc(sizeof(char *), map->height + 1);
	if (!map->grid)
		exit_error(NULL, true);
	map_node = head;
	y = 0;
	while (y < map->height)
	{
		map->grid[y] = ft_strdup(map_node->line);
		if (!map->grid[y])
			exit_error(NULL, true);
		map_node = map_node->next;
		y++;
	}
}
