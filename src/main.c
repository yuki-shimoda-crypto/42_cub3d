/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/12 23:28:21 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// static void	init_game_data(t_game_data *data)
// {
// 	data->map_node = NULL;
// 	data->player_pos = NULL;
// 	data->orientation = '\0';
// 	data->n_texture = NULL;
// 	data->s_texture = NULL;
// 	data->w_texture = NULL;
// 	data->e_texture = NULL;
// 	data->f_color[0] = 0;
// 	data->f_color[1] = 0;
// 	data->f_color[2] = 0;
// 	data->c_color[0] = 0;
// 	data->c_color[1] = 0;
// 	data->c_color[2] = 0;
// }
// 
// int	main(int argc, const char *argv[])
// {
// 	t_cub_file_node		*cub_file_node;
// 	t_game_data			data;
// 
// 	init_game_data(&data);
// 	check_file_name(argc, argv);
// 	cub_file_node = read_cub_file(argv[1]);
// 	check_cub_file(cub_file_node, &data);
// 	free_cub_file_node(cub_file_node);
// 	free_data(&data);
// 	return (0);
// }

void	draw_wall_strip(t_mlx *mlx, t_player *player, t_ray *ray, size_t x)
{
	t_draw	draw;
	size_t	y;

	y = 0;
	calc_wall_strip(&draw, player, ray);
	determine_texture(&draw, ray);
	while (y < WINDOW_HEIGHT)
	{
		calc_texture_coords(&draw, player, ray);
		color_pixel(mlx, &draw, x, y);
		y++;
	}
}

void	ray_casting(t_mlx *mlx)
{
	size_t	x;

	x = 0;
	while (x < WINDOW_WIDTH)
	{
		mlx->ray.angle = mlx->player.direction - (mlx->player.fov / 2)
			+ ((double)x / (double)WINDOW_WIDTH) * mlx->player.fov;
		if (mlx->ray.angle < 0)
			mlx->ray.angle += 2 * M_PI;
		else if (mlx->ray.angle > 2 * M_PI)
			mlx->ray.angle -= 2 * M_PI;
		cast_ray(&mlx->map, &mlx->player, &mlx->ray);
		draw_wall_strip(mlx, &mlx->player, &mlx->ray, x);
		x++;
	}
}

int	draw(void *mlx)
{
	draw_minimap(mlx, &((t_mlx *)mlx)->map);
	ray_casting(mlx);
	return (0);
}

int	event_key_press(int key_num, t_mlx *mlx)
{
	if (key_num == KEY_ESC)
		handle_escape_key(mlx);
	else if (key_num == KEY_W || key_num == KEY_S
		|| key_num == KEY_A || key_num == KEY_D)
		handle_move_key(key_num, mlx);
	else if (key_num == KEY_LEFT || key_num == KEY_RIGHT)
		handle_rotate_key(key_num, mlx);
	return (0);
}

int	main(void)
{
	t_mlx	mlx;

	init_mlx(&mlx);
	mlx_loop_hook(mlx.mlx_ptr, draw, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, event_key_press, &mlx);
	mlx_hook(mlx.win_ptr, 17, 1L << 2, destroy_mlx, &mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
