/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/13 06:33:52 by enogaWa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "cub3d.h"

int	main(int argc, const char *argv[])
{
	t_cub_file_node		*cub_file_node;
	t_game_data			data;

	init_game_data(&data);
	check_file_name(argc, argv);
	cub_file_node = read_cub_file(argv[1]);
	check_cub_file(cub_file_node, &data);
	mlx_func(&data);
	free_cub_file_node(cub_file_node);
	free_data(&data);
	return (0);
}
