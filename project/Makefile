# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 15:00:17 by rcarmen           #+#    #+#              #
#    Updated: 2021/02/11 13:12:37 by rcarmen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cube3D

SRC = main.c parsing_scene.c handle_rgb.c free_stuff.c
OBJ = $(patsubst %.c, %.o, $(SRC))

SRC_DIR = src/

CFLAGS = -Wall -Wextra -Werror

SRC_PATH = $(addprefix ../../$(SRC_DIR), $(SRC))

all: $(NAME)

$(NAME): libft mlx $(OBJ)
	ar rcs $(NAME).a $(OBJ)
	gcc $(CFLAGS) $(SRC_PATH) $(COMPILE_FLAGS) cube3D.a libmlx_Linux.a libft.a -I../../src/ -lX11 -lXext -Lincludes/MiniLib/ -lm -I. -o ../../$(NAME) 

VPATH = ../../src/

%.o: %.c
	gcc $(CFLAGS) $(COMPILE_FLAGS) -I./mlx_linux/ -Imlx_linux -c $< -o $@ -MD

libft: .
	make -C ../../src/libft/ && cp ../../src/libft/libft.a .

mlx:
	$(MAKE) -C ../../src/mlx_linux/ && cp ../../src/mlx_linux/libmlx_Linux.a .

clean:
	make clean --directory=. --makefile=../../src/libft/Makefile
	$(MAKE) clean -C ../../src/mlx_linux/
	rm -rf ../../bin/

fclean:
	rm -f ../../$(NAME)
	make clean --directory=. --makefile=../../src/libft/Makefile
	$(MAKE) clean -C ../../src/mlx_linux/
	rm -rf ../../bin/

re: fclean all
