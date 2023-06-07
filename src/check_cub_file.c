/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 15:56:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/07 16:36:51 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <ctype.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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

static char	*dup_texture_name(t_cub_file_node *node, const char *s)
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

static void	can_open_texture(const char *s)
{
	int	fd;

	fd = open(s, O_RDONLY);
	if (fd == -1)
		exit_error(s, true);
	close(fd);
}

void	check_texture_file(t_game_data *data)
{
	can_open_texture(data->n_texture);
	can_open_texture(data->s_texture);
	can_open_texture(data->w_texture);
	can_open_texture(data->e_texture);
}

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
			data->f_color[j] = atol(&s[i]);
		else
			data->c_color[j] = atol(&s[i]);
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

void	is_under_0_over_255(long num)
{
	if (num < 0 || 255 < num)
		exit_error("RGB values must range from 0 to 255\n", false);
}

void	check_color(t_game_data *data)
{
	is_under_0_over_255(data->f_color[0]);
	is_under_0_over_255(data->f_color[1]);
	is_under_0_over_255(data->f_color[2]);
	is_under_0_over_255(data->c_color[0]);
	is_under_0_over_255(data->c_color[1]);
	is_under_0_over_255(data->c_color[2]);
}

bool	is_texture_color(const char *line)
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

t_map_node	*make_map(t_cub_file_node *node)
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
	print_texture(data);
	print_color(data);
	print_map(data->map_node);
}
