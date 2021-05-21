# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/14 18:06:38 by dcho              #+#    #+#              #
#    Updated: 2021/05/21 08:26:48 by dcho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
# CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I ./includes -I ./libft
# CFLAGS =  -g -fsanitize=address -I ./includes -I ./libft
CFLAGS = -Wall -Wextra -Werror -g -I ./includes -I ./libft

LDFLAGS = -L . -L $(LIBMLX_DIR) -L $(LIBFT_DIR)

RM = rm -f

NAME = cub3D

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

SRCS_B =	./bonus/srcs/main.c							\
			./bonus/srcs/init.c							\
			./bonus/srcs/error.c							\
			./bonus/srcs/free.c							\
			./bonus/srcs/gnl/get_next_line.c				\
			./bonus/srcs/gnl/get_next_line_utils.c			\
			./bonus/srcs/parsing/parser.c					\
			./bonus/srcs/parsing/parser_utils.c			\
			./bonus/srcs/parsing/parser_identifier.c		\
			./bonus/srcs/parsing/parser_identifier_sub.c	\
			./bonus/srcs/parsing/parser_map.c				\
			./bonus/srcs/parsing/map_validation.c			\
			./bonus/srcs/parsing/parser_dup.c				\
			./bonus/srcs/game/game.c						\
			./bonus/srcs/game/key_handling.c				\
			./bonus/srcs/game/texture.c					\
			./bonus/srcs/game/graphic.c					\
			./bonus/srcs/game/color.c						\
			./bonus/srcs/game/raycasting.c					\
			./bonus/srcs/game/sprite.c						\
			./bonus/srcs/game/render.c						\
			./bonus/srcs/game/bmp.c							\
			./bonus/srcs/game/sprite_multi.c

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
		@make -C $(LIBFT_DIR) fclean

re : fclean all

bonus : $(OBJS_B)
		@make -C $(LIBFT_DIR) all
		@make -C $(LIBMLX_DIR) all
		cp $(LIBMLX_DIR)/$(LIBMLX) .
		$(CC) $(CFLAGS) $^ \
		$(LDFLAGS) -lft -lmlx\
		-framework OpenGL -framework AppKit -lz\
		-o cub3D


.PHONY : all clean fclean re

