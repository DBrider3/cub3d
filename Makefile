# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/14 18:06:38 by dcho              #+#    #+#              #
#    Updated: 2021/05/22 14:59:13 by dcho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I ./includes -I ./libft
# CFLAGS =  -g -fsanitize=address -I ./includes -I ./libft
CFLAGS = -Wall -Wextra -Werror -g -I ./includes -I ./libft

LDFLAGS = -L . -L $(LIBMLX_DIR) -L $(LIBFT_DIR)

RM = rm -f

NAME = cub3D
NAME_B = cub3D_B

SRC =	main.c								\
		init.c								\
		error.c								\
		free.c								\
		gnl/get_next_line.c					\
		gnl/get_next_line_utils.c			\
		parsing/parser.c					\
		parsing/parser_utils.c				\
		parsing/parser_identifier.c			\
		parsing/parser_identifier_sub.c		\
		parsing/parser_map.c				\
		parsing/map_validation.c			\
		parsing/parser_dup.c				\
		game/game.c							\
		game/key_handling.c					\
		game/texture.c						\
		game/graphic.c						\
		game/color.c						\
		game/raycasting.c					\
		game/sprite.c						\
		game/render.c						\
		game/bmp.c

SRCS_B =	./bonus/srcs/main_bonus.c							\
			./bonus/srcs/init_bonus.c							\
			./bonus/srcs/error_bonus.c							\
			./bonus/srcs/free_bonus.c							\
			./bonus/srcs/gnl/get_next_line_bonus.c				\
			./bonus/srcs/gnl/get_next_line_utils_bonus.c			\
			./bonus/srcs/parsing/parser_bonus.c					\
			./bonus/srcs/parsing/parser_utils_bonus.c			\
			./bonus/srcs/parsing/parser_identifier_bonus.c		\
			./bonus/srcs/parsing/parser_identifier_sub_bonus.c	\
			./bonus/srcs/parsing/parser_map_bonus.c				\
			./bonus/srcs/parsing/map_validation_bonus.c			\
			./bonus/srcs/parsing/parser_dup_bonus.c				\
			./bonus/srcs/game/game_bonus.c						\
			./bonus/srcs/game/key_handling_bonus.c				\
			./bonus/srcs/game/texture_bonus.c					\
			./bonus/srcs/game/graphic_bonus.c					\
			./bonus/srcs/game/color_bonus.c						\
			./bonus/srcs/game/raycasting_bonus.c					\
			./bonus/srcs/game/sprite_bonus.c						\
			./bonus/srcs/game/render_bonus.c						\
			./bonus/srcs/game/bmp_bonus.c							\
			./bonus/srcs/game/sprite_sort_bonus.c				\
			./bonus/srcs/game/mouse_bonus.c

SRC_DIR = ./srcs/
SRCS = $(addprefix $(SRC_DIR),$(SRC))

OBJS = $(SRCS:.c=.o)
OBJS_B = $(SRCS_B:.c=.o)

LIBMLX = libmlx.dylib
LIBMLX_DIR = ./minilibx_mms_20200219/

LIBFT_DIR = ./libft/

all : $(NAME)

$(NAME) : $(OBJS)
		@make -C $(LIBFT_DIR) all
		@make -C $(LIBMLX_DIR) all
		cp $(LIBMLX_DIR)/$(LIBMLX) .
		$(CC) $(CFLAGS) $^ \
		$(LDFLAGS) -lft -lmlx\
		-framework OpenGL -framework AppKit -lz\
		-o $@

%.o : $(SRC_DIR)/%.c
		$(CC) $(CFLAGS) -o $@ -c $<

clean:
		$(RM) $(OBJS) $(OBJS_B)
		$(RM) $(LIBMLX)
		@make -C $(LIBFT_DIR) clean
		@make -C $(LIBMLX_DIR) clean

fclean: clean
		$(RM) $(NAME)
		$(RM) $(NAME_B)
		@make -C $(LIBFT_DIR) fclean

re : fclean all

bonus : $(NAME_B)

$(NAME_B) : $(OBJS_B)
		@make -C $(LIBFT_DIR) all
		@make -C $(LIBMLX_DIR) all
		cp $(LIBMLX_DIR)/$(LIBMLX) .
		$(CC) $(CFLAGS) $^ \
		$(LDFLAGS) -lft -lmlx\
		-framework OpenGL -framework AppKit -lz\
		-o $@


.PHONY : all clean fclean re

