/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 20:57:09 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/08 20:48:24 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>

void	print_cub_file_node(t_cub_file_node *node)
{
	while (node)
	{
		printf("%s", node->line);
		node = node->next;
	}
}

void	print_texture(t_game_data *data)
{
	printf("%s\n", data->n_texture);
	printf("%s\n", data->s_texture);
	printf("%s\n", data->w_texture);
	printf("%s\n", data->e_texture);
}

void	print_color(t_game_data *data)
{
	printf("F %3ld, %3ld, %3ld\n", data->f_color[0],
		data->f_color[1], data->f_color[2]);
	printf("C %3ld, %3ld, %3ld\n", data->c_color[0],
		data->c_color[1], data->c_color[2]);
}

void	print_map(t_map_node *map)
{
	while (map)
	{
		printf("%s\n", map->line);
		map = map->next;
	}
}
