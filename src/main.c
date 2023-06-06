/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/05 16:58:44 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "libft.h"

//void	check_map(t_map *map)
//{
//}
//
//void	check_word_exists(t_file *file, const char *str)
//{
//}
//
//void	check_identifiers_exist(t_file *file)
//{
//	check_word_exists(file, "NO");
//	check_word_exists(file, "SO");
//	check_word_exists(file, "WE");
//	check_word_exists(file, "EA");
//	check_word_exists(file, "F");
//	check_word_exists(file, "C");
//}
//
//void	check_file(t_file *file, t_map *map)
//{
//	check_identifiers_exist(file);
//}
//
//void	read_file(t_file *file, const char *argv[])
//{
//}


void	init_game_data(t_game_data *data)
{
	data->map_node = NULL;
	data->player_pos = NULL;
	data->orientation = '\0';
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

int	main(int argc, const char *argv[])
{
	t_cub_file_node		*cub_file_node;
	t_game_data			data;

	init_game_data(&data);
	check_file_name(argc, argv);
	cub_file_node = read_cub_file(argv[1]);
	check_cub_file(cub_file_node, &data);
	free_cub_file_node(cub_file_node);
	return (0);
}
