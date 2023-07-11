/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_surrounded_by_walls.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:43:35 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/11 22:17:15 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static bool	is_orientation(char c)
{
	if (c == 'N')
		return (true);
	else if (c == 'S')
		return (true);
	else if (c == 'E')
		return (true);
	else if (c == 'W')
		return (true);
	return (false);
}

static void	start_enqueue(char **dup_map, t_queue **queue)
{
	size_t	x;
	size_t	y;
	size_t	i;
	size_t	j;

	y = 0;
	i = 0;
	i = 0;
	while (dup_map[i])
	{
		x = 0;
		j = 0;
		y++;
		while (dup_map[i][j])
		{
			if (is_orientation(dup_map[i][j]))
			{
				enqueue(queue, x, y);
				return ;
			}
			x++;
			j++;
		}
		i++;
	}
}

#include <stdio.h>

static void	print_dupmap(char **map)
{
	size_t	y;

	y = 0;
	while (map[y])
	{
		printf("%s\n", map[y]);
		y++;
	}
	
}

static void	check_surrounded_by_walls(char **dup_map)
{
	t_queue		*queue;

	queue = NULL;
	start_enqueue(dup_map, &queue);
	while (queue)
	{
		if (can_move_up(dup_map, queue->x, queue->y))//
			enqueue(&queue, queue->x, queue->y - 1);
		if (can_move_down(dup_map, queue->x, queue->y))
			enqueue(&queue, queue->x, queue->y + 1);
		if (can_move_left(dup_map, queue->x, queue->y))
			enqueue(&queue, queue->x - 1, queue->y);
		if (can_move_right(dup_map, queue->x, queue->y))
			enqueue(&queue, queue->x + 1, queue->y);
		dequeue(&queue);
		print_dupmap(dup_map);
	}
}

// static t_map_node	*duplicate_map(t_map_node *map)
// {
// 	t_map_node	*dup_map;
// 	t_map_node	*new_map;

// 	dup_map = NULL;
// 	while (map)
// 	{
// 		new_map = map_node_new(map->line);
// 		map_node_addback(&dup_map, new_map);
// 		map = map->next;
// 	}
// 	return (dup_map);
// }

void	check_map_surrounded_by_walls(char **dup_map)
{
	// t_map_node	*dup_map;
	// char **dup_map;

	// dup_map = duplicate_map(map);
	check_surrounded_by_walls(dup_map);
	free_map_array(dup_map);
}
