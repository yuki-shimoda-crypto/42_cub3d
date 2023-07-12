/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 06:17:14 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/13 06:34:12 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cub3d.h"

void	init_mlx(t_mlx *mlx, t_game_data *data)
{
	mlx->mlx_ptr = safe_mlx_init();
	mlx->win_ptr
		= safe_mlx_new_window(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx");
	init_map(&mlx->map, data->map_node);
	init_player(mlx->map.grid, &mlx->player);
	load_textures(mlx, data);
	mlx->data = data;
}

int	destroy_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}
