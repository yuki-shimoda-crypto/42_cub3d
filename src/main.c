/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/08 20:48:00 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>

static void	init_game_data(t_game_data *data)
{
	data->map_node = NULL;
	data->player_pos = NULL;
	data->orientation = '\0';
	data->n_texture = NULL;
	data->s_texture = NULL;
	data->w_texture = NULL;
	data->e_texture = NULL;
	data->f_color[0] = 0;
	data->f_color[1] = 0;
	data->f_color[2] = 0;
	data->c_color[0] = 0;
	data->c_color[1] = 0;
	data->c_color[2] = 0;
}

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

void	free_data(t_game_data *data)
{
	free(data->n_texture);
	free(data->s_texture);
	free(data->w_texture);
	free(data->e_texture);
}

int	main(int argc, const char *argv[])
{
	t_cub_file_node		*cub_file_node;
	t_game_data			data;

	init_game_data(&data);
	check_file_name(argc, argv);
	cub_file_node = read_cub_file(argv[1]);
	check_cub_file(cub_file_node, &data);
	free_cub_file_node(cub_file_node);
	free_data(&data);
	return (0);
}
