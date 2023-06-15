/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_surrounded_by_walls.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:43:35 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/15 16:12:40 by yshimoda         ###   ########.fr       */
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

static void	start_enqueue(t_map_node *map, t_queue **queue)
{
	size_t	x;
	size_t	y;

	y = 0;
	while (map)
	{
		x = 0;
		y++;
		while (map->line[x])
		{
			if (is_orientation(map->line[x]))
			{
				enqueue(queue, x, y);
				return ;
			}
			x++;
		}
		map = map->next;
	}
}

static void	check_surrounded_by_walls(t_map_node *map)
{
	t_queue		*queue;

	queue = NULL;
	start_enqueue(map, &queue);
	while (queue)
	{
		if (can_move_up(map, queue->x, queue->y))
			enqueue(&queue, queue->x, queue->y - 1);
		if (can_move_down(map, queue->x, queue->y))
			enqueue(&queue, queue->x, queue->y + 1);
		if (can_move_left(map, queue->x, queue->y))
			enqueue(&queue, queue->x - 1, queue->y);
		if (can_move_right(map, queue->x, queue->y))
			enqueue(&queue, queue->x + 1, queue->y);
		dequeue(&queue);
	}
}

static t_map_node	*duplicate_map(t_map_node *map)
{
	t_map_node	*dup_map;
	t_map_node	*new_map;

	dup_map = NULL;
	while (map)
	{
		new_map = map_node_new(map->line);
		map_node_addback(&dup_map, new_map);
		map = map->next;
	}
	return (dup_map);
}

void	check_map_surrounded_by_walls(t_map_node *map)
{
	t_map_node	*dup_map;

	dup_map = duplicate_map(map);
	check_surrounded_by_walls(dup_map);
	free_map(dup_map);
}
