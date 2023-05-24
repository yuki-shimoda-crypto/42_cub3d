/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:24:27 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/24 21:33:10 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"
#include <fcntl.h>

t_cub_file_node	*make_cub_file_node(char *line)
{
	t_cub_file_node	*node;
	
	node = calloc(sizeof(t_cub_file_node), 1);
	if (!node)
		exit_error("calloc error\n", false);
	node->line = line;
	return (node);
}

void	free_cub_file_node(t_cub_file_node *node)
{
	t_cub_file_node	*next;

	while (node)
	{
		next = node->next;
		free(node->line);
		free(node);
		node = next;
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
		node->next = make_cub_file_node(line);
		node = node->next;
	}
	close(fd);
	return (cub_file_node.next);
}
