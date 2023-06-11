/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_element.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 20:07:14 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/07 20:07:53 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
