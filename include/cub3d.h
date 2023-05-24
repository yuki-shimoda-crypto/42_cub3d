/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:44:35 by yshimoda          #+#    #+#             */
/*   Updated: 2023/05/24 22:13:40 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include <stdbool.h>
#include <stddef.h>

// remove
#include <string.h>
#include <stdlib.h>

#define COLOR_RESET	"\033[0m"
#define COLOR_RED	"\033[31m"

typedef	struct s_game_data			t_game_data;
typedef	struct s_map_node			t_map_node;
typedef	struct s_player_pos			t_player_pos;
typedef	struct s_cub_file_node		t_cub_file_node;
typedef	struct s_cub_file_status	t_cub_file_status;
typedef	struct s_cub_file_count		t_cub_file_count;

// save all game data after checking
struct	s_game_data
{
	t_map_node		*map_node;
	t_player_pos	*player_pos;
	char			orientation;
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	long			f_color[3];
	long			c_color[3];
};

// save the map node after checking
struct	s_map_node
{
	t_map_node	*next;
	t_map_node	*pre;
	char	*line;
};

// save current location
struct	s_player_pos
{
	size_t	*x;
	size_t	*y;
};

// use to read *.cub and check content
struct	s_cub_file_node
{
	char		*line;
	t_cub_file_node	*next;
};

// check cub file status
struct	s_cub_file_status
{
	bool	n_texture;
	bool	s_texture;
	bool	w_texture;
	bool	e_texture;
	bool	f_color;
	bool	c_color;
	bool	orientation;
};

// check cub file content count
struct	s_cub_file_count
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

// check
void			exit_error(const char *s, bool perror_flag);

// error
void			check_file_name(int argc, const char *argv[]);

// cub_file_node
void			free_cub_file_node(t_cub_file_node *node);
t_cub_file_node	*make_cub_file_node(char *line);
t_cub_file_node	*read_cub_file(const char *filename);

// debug
void			print_cub_file_node(t_cub_file_node *node);

#endif
