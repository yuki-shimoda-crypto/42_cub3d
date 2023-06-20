/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:02:02 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/10 12:35:30 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_map_node	*make_map(t_cub_file_node *node)
{
	t_map_node	*map;
	t_map_node	*new_map;

	map = NULL;
	while (node)
	{
		new_map = map_node_new(node->line);
		map_node_addback(&map, new_map);
		node = node->next;
	}
	return (map);
}

static bool	is_texture_color(const char *line)
{
	if (!strncmp(line, "F", 1))
		return (true);
	else if (!strncmp(line, "C", 1))
		return (true);
	else if (!strncmp(line, "NO", 2))
		return (true);
	else if (!strncmp(line, "SO", 2))
		return (true);
	else if (!strncmp(line, "WE", 2))
		return (true);
	else if (!strncmp(line, "EA", 2))
		return (true);
	return (false);
}

static t_cub_file_node	*skip_to_map(t_cub_file_node *node)
{
	size_t	i;

	i = 0;
	while (node)
	{
		if (i >= 6 && node->line[0] != '\0')
			break ;
		if (is_texture_color(node->line))
			i++;
		node = node->next;
	}
	return (node);
}

void	input_map(t_cub_file_node *node, t_game_data *data)
{
	node = skip_to_map(node);
	data->map_node = make_map(node);
	if (!data->map_node)
		exit_error("Map is required\n", false);
}
