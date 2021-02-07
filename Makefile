NAME = cube3D

SRC = main.c

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) all -C mlx_linux/
	$(MAKE) all -C libft/
	mv mlx_linux/libmlx_Linux.a .
	mv libft/libft.a .
	ar rcs $(NAME).a $(OBJ)
	gcc $(CFLAGS) ./src/main.c $(NAME).a libft.a libmlx_Linux.a -lX11 -lXext -Lincludes/MiniLib/ -lm -I. -o $(NAME) 

VPATH = ./src/

%.o: %.c
	gcc -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean:
	$(MAKE) clean -C ./libft/
	rm -f 

fclean:
	$(MAKE) fclean -C ./libft/
	rm -f

re: fclean all