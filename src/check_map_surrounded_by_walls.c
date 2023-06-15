/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_surrounded_by_walls.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:43:35 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/12 18:45:10 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_map_node	*move_map_row(t_map_node *map, size_t y)
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

static bool	can_move_right(t_map_node *map, size_t x, size_t y)
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

static bool	can_move_left(t_map_node *map, size_t x, size_t y)
{
	map = move_map_row(map, y);
	map->line[x] = '1';
	if (!map)
		exit_error("The map must be walled off.\n", false);
	if (map->size < x + 1)
		exit_error("The map must be walled off.\n", false);
	if (x == 1)
		exit_error("The map must be walled off.\n", false);
	if (map->line[x - 1] == ' ' || map->line[x - 1] == '\0')
		exit_error("The map must be walled off.\n", false);
	if (map->line[x - 1] == '1')
		return (false);
	if (map->line[x - 1] == '0')
		return (true);
	return (true);
}

static bool	can_move_down(t_map_node *map, size_t x, size_t y)
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

static bool	can_move_up(t_map_node *map, size_t x, size_t y)
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
