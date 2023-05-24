/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:44:35 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/24 12:51:22 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdbool.h>
#include <stddef.h>

// remove
#include <string.h>

#define COLOR_RESET	"\033[0m"
#define COLOR_RED	"\033[31m"

typedef	struct s_data			t_data;
typedef	struct s_map			t_map;
typedef	struct s_pos			t_pos;
typedef	struct s_file_line		t_file_line;
typedef	struct s_file_status	t_file_status;
typedef	struct s_file_content_num	t_file_content_num;

// save all data after checking
struct	s_data
{
	t_map	*map;
	t_pos	*pos;
	char	orientation;
	char	*n_texture;
	char	*s_texture;
	char	*w_texture;
	char	*e_texture;
	long	f_color[3];
	long	c_color[3];
};

// save the map after checking
struct	s_map
{
	t_map	*next;
	t_map	*pre;
	char	*line;
};

// save current location
struct	s_pos
{
	size_t	*x;
	size_t	*y;
};

// use to read *.cub and check content
struct	s_file_line
{
	char		*line;
	t_file_line	*next;
};

// check file status
struct	s_file_status
{
	bool	n_texture;
	bool	s_texture;
	bool	w_texture;
	bool	e_texture;
	bool	f_color;
	bool	c_color;
	bool	orientation;
};

// check file content num
struct	s_file_content_num
{
	size_t	n_texture;
	size_t	s_texture;
	size_t	w_texture;
	size_t	e_texture;
	size_t	f_color;
	size_t	c_color;
	size_t	n;
	size_t	s;
	size_t	w;
	size_t	e;
};

void	exit_error(const char *s);

#endif
