/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:56:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/11 23:01:02 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static void	init_cub_file_count(t_cub_file_count *count)
{
	count->n_texture = 0;
	count->s_texture = 0;
	count->w_texture = 0;
	count->e_texture = 0;
	count->f_color = 0;
	count->c_color = 0;
}

char	**make_map_array(t_cub_file_node	*node)
{
	int		i;
	char	**map;
	// t_cub_file_node	*tmp;

	// tmp = node;
	i = 0;
	while (node)
	{
		i++;
		node = node->next;
	}
	map = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (map[i])
	{
		map[i] = ft_strdup(node->line);
		i++;
		node = node->next;
	}
	map[i] = NULL;
	return (map);
}

void	check_cub_file(t_cub_file_node *node, t_game_data *data)
{
	t_cub_file_count	count;
	// char				**grid;

	init_cub_file_count(&count);
	count_file_element(node, &count);
	check_file_element(&count);
	input_texture_file(node, data);
	check_texture_file(data);
	input_color(node, data);
	check_color(data);
	input_map(node, data);
	// grid = make_map_array(node);
	check_map(node);
}

//	print_texture(data);
//	print_color(data);
//	print_map(data->map_node);
