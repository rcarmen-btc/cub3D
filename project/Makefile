NAME = cube3D

SRC = main.c
OBJ = $(patsubst %.c, %.o, $(SRC))

SRC_DIR = src/

CFLAGS = -Wall -Wextra -Werror

SRC_PATH = $(addprefix ../../$(SRC_DIR), $(SRC))

all: $(NAME)

la:
	ls

$(NAME): libft mlx $(OBJ)
	#$(MAKE) re -C ../../src/libft/ && mv ../../src/libft/libft.a .
	#$(MAKE) -C ../../src/mlx_linux/ && mv ../../src/mlx_linux/libmlx_Linux.a .
	ar rcs $(NAME).a $(OBJ)
	gcc $(CFLAGS) $(SRC_PATH) $(COMPILE_FLAGS) cube3D.a libmlx_Linux.a libft.a -I../../src/ -lX11 -lXext -Lincludes/MiniLib/ -lm -I. -o ../../$(NAME) 

VPATH = ../../src/

%.o: %.c
	gcc $(CFLAGS) $(COMPILE_FLAGS) -I./mlx_linux/ -Imlx_linux -c $< -o $@ -MD

libft: . 
	make --directory=. --makefile=../../src/libft/Makefile

mlx: .
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
