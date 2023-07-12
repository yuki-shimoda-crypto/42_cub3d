/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:41 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/22 13:38:36 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_map_node	*move_map_row(t_map_node *map, size_t y)
{
	size_t	i;

	i = 1;
	while (map && i < y)
	{
		map = map->next;
		i++;
	}
	return (map);
}

bool	can_move_right(t_map_node *map, size_t x, size_t y)
{
	map = move_map_row(map, y);
	map->line[x] = '1';
	if (!map)
		exit_error("The map must be walled off.\n", false);
	if (map->size < x + 1)
		exit_error("The map must be walled off.\n", false);
	if (map->line[x + 1] == ' ' || map->line[x + 1] == '\0')
		exit_error("The map must be walled off.\n", false);
	if (map->line[x + 1] == '1')
		return (false);
	if (map->line[x + 1] == '0')
		return (true);
	return (true);
}

bool	can_move_left(t_map_node *map, size_t x, size_t y)
{
	map = move_map_row(map, y);
	map->line[x] = '1';
	if (!map)
		exit_error("The map must be walled off.\n", false);
	if (map->size < x + 1)
		exit_error("The map must be walled off.\n", false);
	if (x == 0)
		exit_error("The map must be walled off.\n", false);
	if (map->line[x - 1] == ' ' || map->line[x - 1] == '\0')
		exit_error("The map must be walled off.\n", false);
	if (map->line[x - 1] == '1')
		return (false);
	if (map->line[x - 1] == '0')
		return (true);
	return (true);
}

bool	can_move_down(t_map_node *map, size_t x, size_t y)
{
	map = move_map_row(map, y);
	map->line[x] = '1';
	map = map->next;
	if (!map)
		exit_error("The map must be walled off.\n", false);
	if (map->size < x + 1)
		exit_error("The map must be walled off.\n", false);
	if (map->line[x] == ' ' || map->line[x] == '\0')
		exit_error("The map must be walled off.\n", false);
	if (map->line[x] == '1')
		return (false);
	if (map->line[x] == '0')
		return (true);
	return (true);
}

bool	can_move_up(t_map_node *map, size_t x, size_t y)
{
	map = move_map_row(map, y);
	map->line[x] = '1';
	map = map->pre;
	if (!map)
		exit_error("The map must be walled off.\n", false);
	if (map->size < x + 1)
		exit_error("The map must be walled off.\n", false);
	if (map->line[x] == ' ' || map->line[x] == '\0')
		exit_error("The map must be walled off.\n", false);
	if (map->line[x] == '1')
		return (false);
	if (map->line[x] == '0')
		return (true);
	return (true);
}
