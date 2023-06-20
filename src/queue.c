/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:50:58 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/12 14:49:45 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	dequeue(t_queue **queue)
{
	t_queue	*tmp;

	if (!queue || !*queue)
		return ;
	tmp = (*queue)->next;
	free(*queue);
	*queue = tmp;
}

static t_queue	*queue_last(t_queue *queue)
{
	if (!queue)
		return (NULL);
	while (queue->next)
		queue = queue->next;
	return (queue);
}

static t_queue	*queue_new(size_t x, size_t y)
{
	t_queue	*queue;

	queue = malloc(sizeof(t_queue));
	if (!queue)
		exit_error(NULL, true);
	queue->x = x;
	queue->y = y;
	queue->next = NULL;
	return (queue);
}

void	enqueue(t_queue **queue, size_t x, size_t y)
{
	t_queue	*last;
	t_queue	*next;

	if (!queue)
		return ;
	next = queue_new(x, y);
	if (!*queue)
	{
		*queue = next;
		return ;
	}
	last = queue_last(*queue);
	last->next = next;
	return ;
}
