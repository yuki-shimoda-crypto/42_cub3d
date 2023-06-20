/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_func.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 20:04:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/12 14:46:59 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

void	free_cub_file_node(t_cub_file_node *node)
{
	t_cub_file_node	*next;

	while (node)
	{
		next = node->next;
		free(node->line);
		free(node);
		node = next;
	}
}

void	free_map(t_map_node *map)
{
	t_map_node	*tmp;

	while (map)
	{
		tmp = map->next;
		free(map->line);
		free(map);
		map = tmp;
	}
}

void	free_data(t_game_data *data)
{
	free(data->n_texture);
	free(data->s_texture);
	free(data->w_texture);
	free(data->e_texture);
	free_map(data->map_node);
}
