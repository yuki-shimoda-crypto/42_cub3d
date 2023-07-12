/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: enogaWa <enogawa@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 16:44:35 by yshimoda          #+#    #+#             */
/*   Updated: 2023/07/13 05:34:13 by yshimoda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdbool.h>
# include <stddef.h>

// remove
# include <string.h>
# include <ctype.h>

# define COLOR_RESET	"\033[0m"
# define COLOR_RED		"\033[31m"

// # define CLUSTER
# ifdef CLUSTER
#  define KEY_LEFT 123
#  define KEY_UP 126
#  define KEY_RIGHT 124
#  define KEY_DOWN 125
#  define KEY_ESC 53
#  define KEY_W 13
#  define KEY_A 0
#  define KEY_S 1
#  define KEY_D 2
# else
#  define KEY_LEFT 65361
#  define KEY_UP 65362
#  define KEY_RIGHT 65363
#  define KEY_DOWN 65364
#  define KEY_ESC 65307
#  define KEY_W 'w'
#  define KEY_A 'a'
#  define KEY_S 's'
#  define KEY_D 'd'
# endif

#define TILE_SIZE		64
#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	800

#define WALL			'1'

// direction
#define NORTH			(270 * (M_PI / 180))
#define SOUTH			(90 * (M_PI / 180))
#define EAST			(0 * (M_PI / 180))
#define WEST			(180 * (M_PI / 180))

#define FOV				(60 * (M_PI / 180))

#define MOVE_SPEED		0.3

typedef struct s_game_data			t_game_data;
typedef struct s_map_node			t_map_node;
typedef struct s_cub_file_node		t_cub_file_node;
typedef struct s_cub_file_status	t_cub_file_status;
typedef struct s_cub_file_count		t_cub_file_count;
typedef struct s_queue				t_queue;
typedef struct s_draw				t_draw;
typedef enum e_skip					t_skip;
typedef enum e_input				t_input;

typedef struct s_img	t_img;
typedef struct s_map	t_map;
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_mlx	t_mlx;

struct s_img
{
	void	*img;
	char	*data;
	int		bpp;
	int		size_l;
	int		endian;
};

struct s_map
{
	char	**grid;
	size_t	width;
	size_t	height;
};

// fov: field of view
struct s_player
{
	double	x;
	double	y;
	double	direction;
	double	fov;
};

struct s_ray
{
	double	angle;
	double	distance;
	bool	hit_wall;
	int		side;
	double	dir_x;
	double	dir_y;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
};

struct s_mlx
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_map		map;
	t_player	player;
	t_ray		ray;
	t_img		texture[4];
	t_game_data	*data;
};


// save all game data after checking
struct	s_game_data
{
	t_map_node		*map_node;
	char			*n_texture;
	char			*s_texture;
	char			*w_texture;
	char			*e_texture;
	long			f_color[3];
	long			c_color[3];
	size_t			color_floor;
	size_t			color_ceiling;
};

// save the map node after checking
struct	s_map_node
{
	t_map_node	*next;
	t_map_node	*pre;
	char		*line;
	size_t		size;
};

// use to read *.cub and check content
struct	s_cub_file_node
{
	char			*line;
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
};

struct	s_queue
{
	size_t	x;
	size_t	y;
	t_queue	*next;
};

struct	s_draw
{
    double	corrected_distance;
    double	strip_height;
    double	top_pixel;
    double	bottom_pixel;
	int		texture_num;
};

enum	e_skip
{
	SKIP_NUM,
	SKIP_SPACE_COMMA,
};

enum	e_input
{
	INPUT_FLOOR,
	INPUT_CEILING,
};

void			check_color(t_game_data *data);
void			check_cub_file(t_cub_file_node *node, t_game_data *data);
void			check_file_element(t_cub_file_count *count);
void			check_file_name(int argc, const char *argv[]);
void			check_map(t_map_node *map);
void			check_map_surrounded_by_walls(t_map_node *map);
void			check_texture_file(t_game_data *data);
void			count_file_element(t_cub_file_node *node,
					t_cub_file_count *count);
void			exit_error(const char *s, bool perror_flag);
void			input_color(t_cub_file_node *node, t_game_data *data);
void			input_map(t_cub_file_node *node, t_game_data *data);
void			input_texture_file(t_cub_file_node *node, t_game_data *data);
size_t			map_size(t_map_node *map);
void			map_node_clear(t_map_node **map);
t_map_node		*map_node_last(t_map_node *map);
void			map_node_addback(t_map_node **map, t_map_node *next);
t_map_node		*map_node_new(char *str);
t_cub_file_node	*read_cub_file(const char *filename);

// debug
void			print_cub_file_node(t_cub_file_node *node);
void			print_texture(t_game_data *data);
void			print_color(t_game_data *data);
void			print_map(t_map_node *map);

// free
void			free_cub_file_node(t_cub_file_node *node);
void			free_map(t_map_node *map);
void			free_data(t_game_data *data);

// queue
void			enqueue(t_queue **queue, size_t x, size_t y);
void			dequeue(t_queue **queue);

// can move
t_map_node		*move_map_row(t_map_node *map, size_t y);
bool			can_move_right(t_map_node *map, size_t x, size_t y);
bool			can_move_left(t_map_node *map, size_t x, size_t y);
bool			can_move_down(t_map_node *map, size_t x, size_t y);
bool			can_move_up(t_map_node *map, size_t x, size_t y);

// safe mlx
void	*safe_mlx_new_window(void *mlx_ptr, int size_x, int size_y, char *title);
void	*safe_mlx_init(void);


#endif
