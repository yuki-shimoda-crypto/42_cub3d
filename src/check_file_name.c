/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file_name.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 14:21:57 by yshimoda          #+#    #+#             */
/*   Updated: 2023/06/08 20:43:46 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_file_name(int argc, const char *argv[])
{
	if (argc < 2)
		exit_error("The file name must be specified.\n", false);
	else if (argc > 2)
		exit_error("Too many argument\n", false);
	else if (strlen(argv[1]) < 4)
		exit_error("The file name is too short to end with .cub\n", false);
	else if (strcmp(&argv[1][strlen(argv[1]) - 4], ".cub") != 0)
		exit_error("The file must end with .cub\n", false);
}
