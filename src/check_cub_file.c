/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:56:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/05 13:12:34 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	count_inc(t_cub_file_count *count, const char *s)
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

void	count_texture(t_cub_file_node *node, t_cub_file_count *count, const char *s)
{
	while (node)	
	{
		if (!strncmp(node->line, s, 2))
			count_inc(count, s);
		node = node->next;
	}
}

void	count_color(t_cub_file_node *node, t_cub_file_count *count, const char *s)
{
	while (node)
	{
		if (!strncmp(node->line, s, 1))
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

void	check_file_element(t_cub_file_count *count)
{
	if (count->n_texture < 1)
		exit_error("North texture is required.\n", false);
	else if (count->n_texture > 1)
		exit_error("North texture must be one.\n", false);
	else if (count->s_texture < 1)
		exit_error("South texture is required.\n", false);
	else if (count->s_texture > 1)
		exit_error("South texture must be one.\n", false);
	else if (count->w_texture < 1)
		exit_error("West texture is required.\n", false);
	else if (count->w_texture > 1)
		exit_error("West texture must be one.\n", false);
	else if (count->e_texture < 1)
		exit_error("East texture is required.\n", false);
	else if (count->e_texture > 1)
		exit_error("East texture must be one.\n", false);
	else if (count->f_color < 1)
		exit_error("Floor color is required.\n", false);
	else if (count->f_color > 1)
		exit_error("Floor color must be one.\n", false);
	else if (count->c_color < 1)
		exit_error("Ceiling color is required.\n", false);
	else if (count->c_color > 1)
		exit_error("Ceiling color must be one.\n", false);
}

void	init_cub_file_count(t_cub_file_count *count)
{
	count->n_texture = 0;
	count->s_texture = 0;
	count->w_texture = 0;
	count->e_texture = 0;
	count->f_color = 0;
	count->c_color = 0;
	count->orientation = 0;
}

void	check_cub_file(t_cub_file_node *node)
{
	t_cub_file_count	count;

	init_cub_file_count(&count);
	count_file_element(node, &count);
	check_file_element(&count);
}

