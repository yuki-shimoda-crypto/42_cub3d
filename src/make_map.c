/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 15:30:28 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/07 16:21:29 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

size_t	lst_map_size(t_map_node *map)
{
	size_t	i;

	i = 0;
	while (map)
	{
		map = map->next;
		i++;
	}
	return (i);
}

void	map_node_clear(t_map_node **map)
{
	t_map_node	*tmp;

	if (!map || !*map)
		return ;
	while (*map)
	{
		tmp = (*map)->next;
		free((*map)->line);
		free(*map);
		*map = NULL;
		*map = tmp;
	}
	return ;
}

t_map_node	*map_node_last(t_map_node *map)
{
	if (!map)
		return (NULL);
	while (map->next)
		map = map->next;
	return (map);
}

void	map_node_addback(t_map_node **map, t_map_node *next)
{
	t_map_node	*last;

	if (!map || !next)
		return ;
	if (!*map)
	{
		*map = next;
		return ;
	}
	last = map_node_last(*map);
	last->next = next;
	next->pre = last;
	return ;
}

t_map_node	*map_node_new(char *str)
{
	t_map_node	*map;
	char		*map_line;

	map_line = strdup(str);
	if (!map_line)
		exit_error(NULL, true);
	map = malloc(sizeof(t_map_node));
	if (!map)
		exit_error(NULL, true);
	map->line = str;
	map->pre = NULL;
	map->next = NULL;
	return (map);
}
