# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ggiertzu <ggiertzu@student.42berlin.de>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/06 23:26:05 by ggiertzu          #+#    #+#              #
#    Updated: 2024/08/23 11:10:17 by ggiertzu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:= miniRT
CFLAGS  := -g -O0 -Wall -Werror -Wextra -pthread -Ofast
CC		:= gcc

LIBMLX_DIR	:= ./MLX42/build
LIBFT_DIR	:= ./libft
OBJ_DIR	:= obj
SRC_DIR	:= src

LIBMLX	:= $(LIBMLX_DIR)/libmlx42.a
LIBFT	:= $(LIBFT_DIR)/libftprintf.a

HEADERS	:= -I MLX42/include -I $(LIBFT_DIR) -I ./include
LIBS	:= $(LIBMLX) $(LIBFT) -ldl -lglfw -lm
SRCS	:=	src/main.c \
			src/vector_mrt.c \
			src/invert_mrt.c \
			src/matrix_mrt.c \
			src/matrix2_mrt.c \
			src/rays_mrt.c \
			src/aux_mrt.c \
			src/intersect_mrt.c \
			src/intersect2_mrt.c \
			src/camera_mrt.c \
			src/normal_mrt.c \
			src/lighting_mrt.c \
			src/render_mrt.c \
			src/aux_mrt2.c \
			src/init_plane.c \
			src/init_sphere.c

OBJS	:= $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

all: $(NAME)

$(NAME): $(LIBFT) $(LIBMLX) $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBMLX):
	@if [ ! -d MLX42 ]; then \
		echo "Downloading miniLibX..."; \
		git clone https://github.com/codam-coding-college/MLX42.git; \
		cd MLX42; cmake -B build; cmake --build build -j4; \
	fi

$(LIBFT):
	make -C $(LIBFT_DIR)
clean:
	rm -rf $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)
fclean: clean
	rm -rf $(NAME)
	rm -rf MLX42
	make fclean -C $(LIBFT_DIR)
re: clean all

.PHONY: all, clean, fclean, re, libmlx
