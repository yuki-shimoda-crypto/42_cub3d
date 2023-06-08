/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_file_element.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 17:15:07 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/07 20:07:55 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	count_inc(t_cub_file_count *count, const char *s)
{
	if (!strncmp(s, "F", 1))
		count->f_color += 1;
	else if (!strncmp(s, "C", 1))
		count->c_color += 1;
	else if (!strncmp(s, "NO", 2))
		count->n_texture += 1;
	else if (!strncmp(s, "SO", 2))
		count->s_texture += 1;
	else if (!strncmp(s, "WE", 2))
		count->w_texture += 1;
	else if (!strncmp(s, "EA", 2))
		count->e_texture += 1;
}

static void	count_color(t_cub_file_node *node,
			t_cub_file_count *count, const char *s)
{
	while (node)
	{
		if (!strncmp(node->line, s, 1))
			count_inc(count, s);
		node = node->next;
	}
}

static void	count_texture(t_cub_file_node *node,
			t_cub_file_count *count, const char *s)
{
	while (node)
	{
		if (!strncmp(node->line, s, 2))
			count_inc(count, s);
		node = node->next;
	}
}

void	count_file_element(t_cub_file_node *node, t_cub_file_count *count)
{
	count_texture(node, count, "NO");
	count_texture(node, count, "SO");
	count_texture(node, count, "WE");
	count_texture(node, count, "EA");
	count_color(node, count, "F");
	count_color(node, count, "C");
}
