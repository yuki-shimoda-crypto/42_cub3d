/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:24:27 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/08 20:52:12 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

//remove to import ft_calloc
#include <stdlib.h>

static t_cub_file_node	*make_cub_file_node(char *line)
{
	t_cub_file_node	*node;

	node = ft_calloc(sizeof(t_cub_file_node), 1);
	if (!node)
		exit_error("ft_calloc error\n", false);
	node->line = line;
	return (node);
}

static void	newline_to_null(char *line)
{
	while (*line)
	{
		if (*line == '\n')
			*line = '\0';
		line++;
	}
}

t_cub_file_node	*read_cub_file(const char *filename)
{
	int				fd;
	char			*line;
	t_cub_file_node	*node;
	t_cub_file_node	cub_file_node;

	cub_file_node.next = NULL;
	node = &cub_file_node;
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		exit_error(filename, true);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		newline_to_null(line);
		node->next = make_cub_file_node(line);
		node = node->next;
	}
	close(fd);
	return (cub_file_node.next);
}
