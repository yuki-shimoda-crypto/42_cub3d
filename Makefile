# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yshimoda <yshimoda@student.42tokyo.jp>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/16 19:51:43 by yshimoda          #+#    #+#              #
#    Updated: 2023/06/08 20:58:50 by yshimoda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	cub3D
SRC_DIR		=	src
OBJ_DIR		=	obj
DEBUG_DIR	=	obj_debug
INC_DIR		=	include
LIBFT_DIR	=	libft
MLX_DIR		=	minilibx-linux

SRCS		=	src/check_color.c				\
				src/check_cub_file.c			\
				src/check_file_element.c		\
				src/check_file_name.c			\
				src/check_texture_file.c		\
				src/count_file_element.c		\
				src/debug.c						\
				src/error.c						\
				src/input_color.c				\
				src/input_map.c					\
				src/input_texture_file.c		\
				src/main.c						\
				src/make_map.c					\
				src/read_cub_file.c

OBJS		=	$(SRCS:%.c=$(OBJ_DIR)/%.o)
DEBUG_OBJS	=	$(SRCS:%.c=$(DEBUG_DIR)/%.o)
INCLUDE		=	-I $(INC_DIR) -I $(MLX_DIR)

LIBFT		=	$(LIBFT_DIR)/libft.a
MLX			=	$(MLX_DIR)/libmlx.a
LIBS		=	$(LIBFT) $(MLX)

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror
DEBUG_FLUG	=	-g -fsanitize=address -fsanitize=undefined

ALLOW_FUNC	=	open|close|read|write|printf|malloc|free|perror|strerror|exit
NORM		=	norminette

ifeq ($(shell uname -s), Linux)
DEBUG_FLUG		+=	-fsanitize=leak
CHECK_FUNC	=	nm -u $(NAME) | grep -vwE "U ($(ALLOW_FUNC))"
else
CHECK_FUNC	=	nm -u $(NAME) | grep -vwE "_($(ALLOW_FUNC))"
endif

ifneq ($(shell command -v ccache), )
CCACHE			=	ccache
endif

MAPS		=	map/subject.cub

$(OBJ_DIR)/%.o:%.c
			@mkdir -p $(@D)
			$(CCACHE) $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(DEBUG_DIR)/%.o:%.c
			@mkdir -p $(@D)
			$(CCACHE) $(CC) $(CFLAGS) $(DEBUG_FLUG) $(INCLUDE) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJS) $(MLX)
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

.PHONY:	all clean fclean re bonus debug norm play
