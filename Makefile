# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 15:00:17 by rcarmen           #+#    #+#              #
#    Updated: 2021/02/16 03:16:16 by rcarmen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3D

CFLAGS = -Wall -Wextra -Werror -MD -O3 

SRC = main.c parsing_scene.c handle_rgb.c free_stuff.c init.c handle_hooks.c shapaes.c print_line.c print_ray.c error.c validation.c
OBJ = $(patsubst %.c, %.o, $(SRC))
INC = libft.h  linux_kcode.h  main.h  mlx.h

SRC_DIR = src
OBJ_DIR = $(SRC_DIR)/
INC_DIR = include

SRC_PATH = $(addprefix $(SRC_DIR)/, $(SRC))
OBJ_PATH = $(addprefix $(OBJ_DIR)/, $(OBJ))
INC_PATH = $(addprefix $(INC_DIR)/, $(INC))

LIBS = src/libft/libft.a src/mlx_linux/libmlx_Linux.a -lX11 -lXext -Lincludes/MiniLib/ -lm 

BIN = bin/

all: libft.a mlx $(NAME)

$(NAME): $(OBJ) $(INC_PATH)
	$(CC) -Lmlx_linux -L/usr/lib -Imlx_linux $(OBJ) $(LIBS) -lz -o $(NAME)

VPATH = src

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include $(DEBUG) $(addprefix -I, $(INC_DIR)) -Imlx_linux -O3 -c $< -o $@

libft.a: .  
	@$(MAKE) -C src/libft

mlx:
	@$(MAKE) -C src/mlx_linux/

clean:
	@-rm -f $(OBJ)
	@$(MAKE) fclean -C src/libft
	@$(MAKE) clean -C src/mlx_linux

fclean: clean
	@rm -f $(NAME)

re: fclean all
