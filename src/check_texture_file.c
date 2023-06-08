/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 18:56:39 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/08 20:46:50 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

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
