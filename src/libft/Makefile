# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rcarmen <rcarmen@student.21-school.ru>     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/03 15:00:17 by rcarmen           #+#    #+#              #
#    Updated: 2021/02/11 12:32:55 by rcarmen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

INC = libft.h
SRC =	ft_atoi.c     ft_isascii.c    ft_itoa.c          ft_lstiter.c  ft_memccpy.c  ft_memmove.c     ft_putstr_fd.c  ft_strjoin.c  ft_strncmp.c  ft_substr.c\
		ft_bzero.c    ft_isdigit.c    ft_lstadd_back.c   ft_lstlast.c  ft_memchr.c   ft_memset.c      ft_split.c      ft_strlcat.c  ft_strnew.c   ft_tolower.c\
		ft_calloc.c   ft_isprint.c    ft_lstadd_front.c  ft_lstmap.c   ft_memcmp.c   ft_putchar_fd.c  ft_strchr.c     ft_strlcpy.c  ft_strnstr.c  ft_toupper.c\
		ft_isalnum.c  ft_isspace.c    ft_lstclear.c      ft_lstnew.c   ft_memcpy.c   ft_putendl_fd.c  ft_strcpy.c     ft_strlen.c   ft_strrchr.c  get_next_line.c\
		ft_isalpha.c  ft_itoa_base.c  ft_lstdelone.c     ft_lstsize.c  ft_memdel.c   ft_putnbr_fd.c   ft_strdup.c     ft_strmapi.c  ft_strtrim.c
OBJ =	$(patsubst %.c, %.o, $(SRC))

INC_DIR = ../../src/libft/inc/
SRC_DIR = ../../src/libft/src/
OBJ_DIR = ../../src/libft/od/

SRC_PATH = $(addprefix $(SRC_DIR), $(SRC))
OBJ_PATH = $(addprefix $(OBJ_DIR), $(OBJ))
D_PATH = $(patsubst %.o, %.d, $(OBJ_PATH))

CFLAGS = -Wall -Wextra -Werror
OPT_FLUGS = -O -g3

all: od $(NAME)

od:
	mkdir -p ../../src/libft/od/

$(NAME): $(OBJ_PATH)
	ar rcs $(NAME) $?

VPATH = $(SRC_DIR)

$(OBJ_DIR)%.o: %.c
	gcc $(CFLAGS) $(OPT_FLUGS) -c $< -o $@ -MD -I$(INC_DIR)

include	$(wildcard $(D_PATH))

print-%: ; @echo $*=$($*)

clean:
	rm -f $(OBJ_PATH) $(D_PATH) ../../src/libft/od/libft.d
	rm -rf ../../src/libft/od/

fclean: clean
	rm -f libft.a

re: fclean all

.PHONY: all clean fclean re
