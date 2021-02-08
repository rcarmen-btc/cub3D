NAME = cube3D

SRC = main.c
OBJ = $(patsubst %.c, %.o, $(SRC))
INC = 

SRC_DIR = src/

CFLAGS = -Wall -Wextra -Werror

SRC_PATH = $(addprefix ../../$(SRC_DIR), $(SRC))
INC_PATH = 

all: $(NAME)

la:
	ls

$(NAME): libft mlx $(OBJ)
	#$(MAKE) re -C ../../src/libft/ && mv ../../src/libft/libft.a .
	#$(MAKE) -C ../../src/mlx_linux/ && mv ../../src/mlx_linux/libmlx_Linux.a .
	ar rcs $(NAME).a $(OBJ)
	gcc $(CFLAGS) $(SRC_PATH) cube3D.a libmlx_Linux.a libft.a -I../../src/ -lX11 -lXext -Lincludes/MiniLib/ -lm -I. -o ../../$(NAME) 

VPATH = ../../src/

%.o: %.c
	gcc $(CFLAGS) -I./mlx_linux/ -Imlx_linux -O3 -c $< -o $@ -MD

libft: . 
	make --directory=. --makefile=../../src/libft/Makefile

mlx: .
	$(MAKE) -C ../../src/mlx_linux/ && mv ../../src/mlx_linux/libmlx_Linux.a .

clean:
	$(MAKE) clean -C ../src/libft/
	#rm -f 

fclean:
	$(MAKE) fclean -C ../src/libft/
	#rm -f

re: fclean all
