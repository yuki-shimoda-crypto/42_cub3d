/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:56:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/12 18:56:28 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	init_cub_file_count(t_cub_file_count *count)
{
	count->n_texture = 0;
	count->s_texture = 0;
	count->w_texture = 0;
	count->e_texture = 0;
	count->f_color = 0;
	count->c_color = 0;
}

void	check_cub_file(t_cub_file_node *node, t_game_data *data)
{
	t_cub_file_count	count;

	init_cub_file_count(&count);
	count_file_element(node, &count);
	check_file_element(&count);
	input_texture_file(node, data);
	check_texture_file(data);
	input_color(node, data);
	check_color(data);
	input_map(node, data);
	check_map(data->map_node);
//	print_texture(data);
//	print_color(data);
//	print_map(data->map_node);
}
