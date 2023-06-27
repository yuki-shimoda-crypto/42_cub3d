# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 19:51:43 by yshimoda          #+#    #+#              #
#    Updated: 2023/06/22 13:56:34 by yshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
SRC_DIR		=	src
OBJ_DIR		=	obj
DEBUG_DIR	=	obj_debug
INC_DIR		=	include
LIBFT_DIR	=	libft
MLX_DIR		=	minilibx-linux

SRCS		=	src/can_move.c							\
				src/check_color.c						\
				src/check_cub_file.c					\
				src/check_file_element.c				\
				src/check_file_name.c					\
				src/check_map.c							\
				src/check_map_surrounded_by_walls.c		\
				src/check_texture_file.c				\
				src/count_file_element.c				\
				src/debug.c								\
				src/error.c								\
				src/free_func.c							\
				src/input_color.c						\
				src/input_map.c							\
				src/input_texture_file.c				\
				src/main.c								\
				src/make_map.c							\
				src/read_cub_file.c						\
				src/queue.c



OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
DEBUG_OBJS	=	$(SRCS:%.c=$(DEBUG_DIR)/%.o)
INCLUDE		=	-I $(INC_DIR) -I $(MLX_DIR)

MATH		=	-lm
LIBFT		=	$(LIBFT_DIR)/libft.a
MLX_LINUX	=	$(MLX_DIR)/libmlx.a
LIBS		=	$(MATH) $(LIBFT) $(MLX)

CC			=	cc
# CFLAGS		=	-Wall -Wextra -Werror
CFLAGS		=	-Wall -Wextra
DEBUG_FLUG	=	-g -fsanitize=address -fsanitize=undefined

ALLOW_FUNC	=	open|close|read|write|printf|malloc|free|perror|strerror|exit
NORM		=	norminette

ifeq ($(shell uname -s), Linux)
DEBUG_FLUG		+=	-fsanitize=leak
CHECK_FUNC	=	nm -u $(NAME) | grep -vwE "U ($(ALLOW_FUNC))"
LIBS		+=	$(MLX) -lXext -lX11
else
CHECK_FUNC	=	nm -u $(NAME) | grep -vwE "_($(ALLOW_FUNC))"
LIBS		+=	-lmlx -framework OpenGL -framework AppKit
endif

ifneq ($(shell command -v ccache), )
CCACHE			=	ccache
endif

MAPS		=	map/subject.cub

MAPS_ERROR		=	map/invalid_01_empty.cub								\
					map/invalid_02_filename.cu								\
					map/invalid_03_without_NO.cub							\
					map/invalid_04_without_SO.cub							\
					map/invalid_05_without_WE.cub							\
					map/invalid_06_without_EA.cub							\
					map/invalid_07_without_F.cub							\
					map/invalid_08_without_C.cub							\
					map/invalid_09_more_than_one_NORTH.cub					\
					map/invalid_10_more_than_one_SOUTH.cub					\
					map/invalid_11_more_than_one_WEST.cub					\
					map/invalid_12_more_than_one_EAST.cub					\
					map/invalid_13_more_than_one_F.cub						\
					map/invalid_14_more_than_one_C.cub						\
					map/invalid_15_without_floor_r.cub						\
					map/invalid_16_without_floor_g.cub						\
					map/invalid_17_without_floor_b.cub						\
					map/invalid_18_without_ceiling_r.cub					\
					map/invalid_19_without_ceiling_g.cub					\
					map/invalid_20_without_ceiling_b.cub					\
					map/invalid_21_over_255.cub								\
					map/invalid_22_over_int_max.cub							\
					map/invalid_23_over_long_max.cub						\
					map/invalid_24_under_0.cub								\
					map/invalid_25_under_int_min.cub						\
					map/invalid_26_under_long_min.cub						\
					map/invalid_27_Empty_map_1.cub							\
					map/invalid_28_Empty_map_2.cub							\
					map/invalid_29_Unexpected_char.cub						\
					map/invalid_30_Empty_line.cub							\
					map/invalid_31_Two_or_more_directions.cub				\
					map/invalid_32_Not_surrounded_by_walls_1_top.cub		\
					map/invalid_33_Not_surrounded_by_walls_2_bottom.cub		\
					map/invalid_34_Not_surrounded_by_walls_3_left.cub		\
					map/invalid_35_Not_surrounded_by_walls_4_right.cub		\
					map/invalid_36_Not_surrounded_by_walls_5_right.cub

$(OBJ_DIR)/%.o:%.c
			@mkdir -p $(@D)
			$(CCACHE) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(DEBUG_DIR)/%.o:%.c
			@mkdir -p $(@D)
			$(CCACHE) $(CC) $(CFLAGS) $(DEBUG_FLUG) $(INCLUDE) -c $< -o $@

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			$(CCACHE) $(CC) $(CFLAGS) $(INCLUDE) -o $(NAME) $(OBJS) $(LIBS)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

$(MLX):	
			$(MAKE) -C $(MLX_DIR)

all:	$(NAME)

clean:
		$(RM) -r $(OBJ_DIR)
		$(RM) -r $(DEBUG_DIR)
		$(MAKE) -C $(LIBFT_DIR) fclean
		$(MAKE) -C $(MLX_DIR) clean

fclean:	clean
		$(RM) $(NAME)

re:		fclean all

bonus:	re

debug:	$(LIBFT) $(DEBUG_OBJS) $(MLX)
		$(CCACHE) $(CC) $(CFLAGS) $(DEBUG_FLUG) $(INCLUDE) -o $(NAME) $(DEBUG_OBJS) $(LIBS)

norm:	
	$(CHECK_FUNC)
	$(NORM) $(SRC_DIR) $(INC_DIR) $(LIBFT_DIR)

play:
	for map in $(MAPS); do		\
	echo $$map;					\
	./$(NAME) $$map; done
	@echo "finish"

error:
	for map in $(MAPS_ERROR); do	\
	echo -e "$$map\n";						\
	cat $$map;						\
	./$(NAME) $$map;				\
	echo -e "\n---------------"; done
	@echo "finish"

.PHONY:	all clean fclean re bonus debug norm play
