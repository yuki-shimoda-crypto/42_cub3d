/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:56:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/06 19:25:19 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <ctype.h>
#include <stdio.h>

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

void	count_texture(t_cub_file_node *node,
			t_cub_file_count *count, const char *s)
{
	while (node)
	{
		if (!strncmp(node->line, s, 2))
			count_inc(count, s);
		node = node->next;
	}
}

void	count_color(t_cub_file_node *node,
			t_cub_file_count *count, const char *s)
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

// void	check_texture_file(t_cub_file_node *node, t_game_data *data)
// {
// }

char	*dup_texture_name(t_cub_file_node *node, const char *s)
{
	char	*texture;
	size_t	i;

	while (node)
	{
		if (!strncmp(node->line, s, 2))
			break ;
		node = node->next;
	}
	i = 2;
	while (isspace(node->line[i]))
		i++;
	texture = strdup(&node->line[i]);
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

// char	*extract_number()
// {
// }

char	*extract_line(t_cub_file_node *node, const char *s)
{
	while (node)
	{
		if (!strncmp(node->line, s, strlen(s)))
			break ;
		node = node->next;
	}
	if (node)
		return (node->line);
	else
		exit_error("Line does not exist\n", false);
	return (NULL);
}

static void	skip_line(const char *s, size_t *i, t_skip flag)
{
	if (flag == SKIP_NUM)
	{
		while (s[*i] && (isdigit(s[*i]) || s[*i] == '-' || s[*i] == '+'))
			*i += 1;
	}
	else
	{
		while (s[*i])
		{
			if (isspace(s[*i]) || s[*i] == ',')
				*i += 1;
			else if (isdigit(s[*i]) || s[*i] == '-' || s[*i] == '+')
				break ;
			else
				exit_error("Floor and Ceiling are spaces, commas, +, -, and numbers only\n", false);
		}
	}
}

static void	input_number(const char *s, t_game_data *data, t_input flag)
{
	size_t	i;
	size_t	j;
	
	i = 1;
	j = 0;
	while (s[i] && j < 3)
	{
		skip_line(s, &i, SKIP_SPACE_COMMA);
//		printf("%s\n", &s[i]);
		if (flag == INPUT_FLOOR)
			data->f_color[j] = atoi(&s[i]);
		else
			data->c_color[j] = atoi(&s[i]);
		if (!(isdigit(s[i]) || s[i] == '-' || s[i] == '+'))
			break ;
		skip_line(s, &i, SKIP_NUM);
//		printf("%s\n", &s[i]);
		j++;
	}
	if (j != 3)
		exit_error("Three RGB values are required.\n", false);
}

void	input_color(t_cub_file_node *node, t_game_data *data)
{
	char	*line;

	line = extract_line(node, "F");
	input_number(line, data, INPUT_FLOOR);
	line = extract_line(node, "C");
	input_number(line, data, INPUT_CEILING);
}

//void	check_color()
//{
//	
//}

void	check_cub_file(t_cub_file_node *node, t_game_data *data)
{
	t_cub_file_count	count;

	init_cub_file_count(&count);
	count_file_element(node, &count);
	check_file_element(&count);
	input_texture_file(node, data);
//	check_texture_file();
	input_color(node, data);
//	check_color(data);
	printf("%d\n", data->f_color[0]);
	printf("%d\n", data->f_color[1]);
	printf("%d\n", data->f_color[2]);
	printf("%d\n", data->c_color[0]);
	printf("%d\n", data->c_color[1]);
	printf("%d\n", data->c_color[2]);
//	check_texture_file(data);
}
