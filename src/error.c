/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/23 20:16:28 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/24 14:16:46 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	exit_error(const char *s, bool perror_flag)
{
	write(STDERR_FILENO, COLOR_RED, strlen(COLOR_RED));
	write(STDERR_FILENO, "Error\n", strlen("Error\n"));
	write(STDERR_FILENO, COLOR_RESET, strlen(COLOR_RESET));
	if (s && !perror_flag)
		write(STDERR_FILENO, s, strlen(s));
	else if (perror_flag)
		perror(s);
	exit(EXIT_FAILURE);
}
