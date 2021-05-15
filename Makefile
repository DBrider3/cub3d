# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dcho <dcho@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/14 18:06:38 by dcho              #+#    #+#              #
#    Updated: 2021/05/15 21:13:18 by dcho             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -fsanitize=address -I ./includes -I ./libft
# CFLAGS = -Wall -Wextra -Werror -I ./includes -I ./libft

LDFLAGS = -L . -L $(LIBMLX_DIR) -L $(LIBFT_DIR)

RM = rm -f

NAME = cub3D

SRC =	main.c						\
		gnl/get_next_line.c			\
		gnl/get_next_line_utils.c	\
		init.c						\
		parser.c					\
		parser_utils.c				\
		parser_identifier.c			\
		parser_identifier_sub.c		\
		parser_map.c				\
		map_validation.c			\
		error.c						\
		parser_dup.c				\
		free.c						\
		game.c						\
		key_handling.c				\
		texture.c					\
		calc.c						\
		color.c


SRC_DIR = ./srcs/
SRCS = $(addprefix $(SRC_DIR),$(SRC))

OBJS = $(SRCS:.c=.o)

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
		$(RM) $(OBJS)
		$(RM) $(LIBMLX)
		@make -C $(LIBFT_DIR) clean
		@make -C $(LIBMLX_DIR) clean

fclean: clean
		$(RM) $(NAME)
		@make -C $(LIBFT_DIR) fclean


re : fclean all

.PHONY : all clean fclean re

