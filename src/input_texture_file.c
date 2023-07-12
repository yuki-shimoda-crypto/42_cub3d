/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_texture_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:57:26 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/08 19:04:34 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static char	*dup_texture_name(t_cub_file_node *node, const char *s)
{
	char	*texture;
	size_t	i;

	while (node)
	{
		if (!ft_strncmp(node->line, s, 2))
			break ;
		node = node->next;
	}
	i = 2;
	while (ft_isspace(node->line[i]))
		i++;
	texture = ft_strdup(&node->line[i]);
	if (!texture)
		exit_error("malloc error\n", false);
	return (texture);
}

void	input_texture_file(t_cub_file_node *node, t_game_data *data)
{
	data->n_texture = dup_texture_name(node, "NO");
	data->s_texture = dup_texture_name(node, "SO");
	data->w_texture = dup_texture_name(node, "WE");
	data->e_texture = dup_texture_name(node, "EA");
}
