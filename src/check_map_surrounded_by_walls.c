/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_surrounded_by_walls.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 22:43:35 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/12 22:14:11 by yshimoda         ###   ########.fr       */
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

static char	**duplicate_map(t_map_node *map)
{
	t_map_node	*head;
	size_t		height;
	size_t		y;
	char		**dup_map;

	head = map;
	height = 0;
	while (map)
	{
		height += 1;
		map = map->next;
	}
	dup_map = calloc(sizeof(char *), height + 1);
	map = head;
	y = 0;
	while (y < height)
	{
		dup_map[y] = strdup(map->line);
		if (!dup_map[y])
			exit_error(NULL, true);
		map = map->next;
		y++;
	}
	return (dup_map);
}

void	check_map_surrounded_by_walls(t_map_node *map)
{
	char		**dup_map;

	grid = duplicate_map(map);
	check_surrounded_by_walls(dup_map);
	free_map(dup_map);
}
