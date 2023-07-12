/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 18:00:47 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/08 20:50:09 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

static char	*extract_line(t_cub_file_node *node, const char *s)
{
	while (node)
	{
		if (!ft_strncmp(node->line, s, ft_strlen(s)))
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
		while (s[*i] && (ft_isdigit(s[*i]) || s[*i] == '-' || s[*i] == '+'))
			*i += 1;
	}
	else
	{
		while (s[*i])
		{
			if (ft_isspace(s[*i]) || s[*i] == ',')
				*i += 1;
			else if (ft_isdigit(s[*i]) || s[*i] == '-' || s[*i] == '+')
				break ;
			else
				exit_error("Floor and Ceiling are spaces, \
					commas, +, -, and numbers only\n", false);
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
		if (flag == INPUT_FLOOR)
			data->f_color[j] = ft_atol(&s[i]);
		else
			data->c_color[j] = ft_atol(&s[i]);
		if (!(ft_isdigit(s[i]) || s[i] == '-' || s[i] == '+'))
			break ;
		skip_line(s, &i, SKIP_NUM);
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
