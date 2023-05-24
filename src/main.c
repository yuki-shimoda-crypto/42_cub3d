/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 19:28:11 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/24 12:37:39 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <string.h>

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
//

void	check_file_name(int argc, const char *argv[])
{
	if (argc < 2)
		exit_error("The file name must be specified.\n");
	else if (argc > 2)
		exit_error("Too many argument\n");
	else if (strlen(argv[1]) < 4)
		exit_error("The file name is too short to end with .cub\n");
	else if (strcmp(&argv[1][strlen(argv[1]) - 4], ".cub"))
		exit_error("The file must end with .cub\n");
		
}

int	main(int argc, const char *argv[])
{
	check_file_name(argc, argv);
//	read_file(&file, argv);
//	check_file(&file, &map);
//	check_map(&map);
	return (0);
}
