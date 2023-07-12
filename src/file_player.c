/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 23:16:29 by enogaWa           #+#    #+#             */
/*   Updated: 2023/07/12 23:16:30 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

void	init_player(t_player *player)
{
	player->x = 4.3;
	player->y = 4.3;
	player->direction = NORTH;
	player->fov = FOV;
}

void	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr
		= mlx_new_window(mlx->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "mlx");
	init_player(&mlx->player);
	init_map(&mlx->map, &mlx->player);
	load_textures(mlx);
	printf_map(mlx->map.grid);
}

int	destroy_mlx(t_mlx *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}
