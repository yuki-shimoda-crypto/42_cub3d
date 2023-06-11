/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cub_file_5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 19:00:50 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/07 19:01:28 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	is_under_0_over_255(long num)
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
