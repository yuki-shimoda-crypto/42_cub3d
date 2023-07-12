/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:20:55 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/13 06:26:59 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cub3d.h"

void	mlx_func(t_game_data *data)
{
	t_mlx	mlx;

	init_mlx(&mlx, data);
	mlx_loop_hook(mlx.mlx_ptr, ray_cast_and_draw, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, event_key_press, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 2, destroy_mlx, &mlx);
	mlx_loop(mlx.mlx_ptr);
}

void	init_game_data(t_game_data *data)
{
	data->map_node = NULL;
	data->n_texture = NULL;
	data->s_texture = NULL;
	data->w_texture = NULL;
	data->e_texture = NULL;
	data->f_color[0] = 0;
	data->f_color[1] = 0;
	data->f_color[2] = 0;
	data->c_color[0] = 0;
	data->c_color[1] = 0;
	data->c_color[2] = 0;
}
