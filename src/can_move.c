/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   can_move.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 16:10:41 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/11 18:40:12 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// t_map_node	*move_map_row(t_map_node *map, size_t y)
// {
// 	size_t	i;

// 	i = 1;
// 	while (map && i < y)
// 	{
// 		map = map->next;
// 		i++;
// 	}
// 	return (map);
// }

bool	can_move_right(char **dup_map, size_t x, size_t y)
{
	dup_map[y][x] = '1';
	if (!dup_map)
		exit_error("The map must be walled off.\n", false);
	if (strlen(dup_map[y - 1]) < x + 1)//
		exit_error("The map must be walled off.\n", false);
	if (dup_map[y][x + 1] == ' ' || dup_map[y][x + 1] == '\0')
		exit_error("The map must be walled off.\n", false);
	if (dup_map[y][x + 1] == '1')
		return (false);
	if (dup_map[y][x + 1] == '0')
		return (true);
	return (true);
}

bool	can_move_left(char **dup_map, size_t x, size_t y)
{
	dup_map[y][x] = '1';
	if (!dup_map)
		exit_error("The map must be walled off.\n", false);
	if (strlen(dup_map[y - 1]) < x + 1)//
		exit_error("The map must be walled off.\n", false);
	if (x == 1)
		exit_error("The map must be walled off.\n", false);
	if (dup_map[y][x - 1] == ' ' || dup_map[y][x - 1] == '\0')
		exit_error("The map must be walled off.\n", false);
	if (dup_map[y][x - 1] == '1')
		return (false);
	if (dup_map[y][x - 1] == '0')
		return (true);
	return (true);
}

bool	can_move_down(char **dup_map, size_t x, size_t y)
{
	dup_map[y][x] = '1';
	if (!dup_map)
		exit_error("The map must be walled off.\n", false);
	if (strlen(dup_map[y + 1]) < x + 1)
		exit_error("The map must be walled off.\n", false);
	if (dup_map[y + 1][x] == ' ' || dup_map[y][x] == '\0')
		exit_error("The map must be walled off.\n", false);
	if (dup_map[y + 1][x] == '1')
		return (false);
	if (dup_map[y + 1][x] == '0')
		return (true);
	return (true);
}

bool	can_move_up(char	**dup_map, size_t x, size_t y)
{
	// dup_map = move_map_row(dup_map, y);
	dup_map[y][x] = '1';
	if (!dup_map)
		exit_error("The map must be walled off.\n", false);
	if (strlen(dup_map[y - 1]) < x + 1)
		exit_error("The map must be walled off.\n", false);
	if (dup_map[y - 1][x] == ' ' || dup_map[y - 1][x] == '\0')
		exit_error("The map must be walled off.\n", false);
	if (dup_map[y - 1][x] == '1')
		return (false);
	if (dup_map[y - 1][x] == '0')
		return (true);
	return (true);
}
