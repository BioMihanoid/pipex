NAME = pipex

FLAGS = -Wall -Wextra -Werror -MD

CC = gcc

SRC = pipex.c	\
	  utils.c

HEADER = pipex.h

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C libft
	gcc $(FLAGS) libft/libft.a $(SRC) -o $(NAME)

%o:	%.c libft/*.c
	gcc $(FLAGS) -c $< -o $@

clean:
		 make clean -C libft
		 rm -rf $(OBJ) *.d

fclean:	 clean
		 make fclean -C libft
		 rm -rf $(NAME) *.d

re:		 fclean all

.PHONY: clean fclean all re