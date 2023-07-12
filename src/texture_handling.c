/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:28:06 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/13 06:37:57 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cub3d.h"

void	load_textures(t_mlx *mlx, t_game_data *data)
{
	int		i;
	int		x;
	int		y;
	char	*texture_files[4];

	texture_files[0] = data->n_texture;
	texture_files[1] = data->s_texture;
	texture_files[2] = data->e_texture;
	texture_files[3] = data->w_texture;
	i = 0;
	while (i < 4)
	{
		mlx->texture[i].img
			= mlx_xpm_file_to_image(mlx->mlx_ptr, texture_files[i], &x, &y);
		if (mlx->texture[i].img == NULL)
			exit_error("Can not file to mlx image\n", false);
		mlx->texture[i].data
			= mlx_get_data_addr(mlx->texture[i].img, &mlx->texture[i].bpp,
				&mlx->texture[i].size_l, &mlx->texture[i].endian);
		i++;
	}
}

void	make_color(t_game_data *data, long *f_color, long *c_color)
{
	data->color_floor = f_color[0] * (16 * 16 * 16 * 16)
		+ f_color[1] * (16 * 16) + f_color[2];
	data->color_ceiling = c_color[0] * (16 * 16 * 16 * 16)
		+ c_color[1] * (16 * 16) + c_color[2];
}
