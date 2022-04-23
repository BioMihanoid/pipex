NAME = pipex

FLAGS = -Wall -Wextra -Werror -MD

CC = gcc

SRC = pipex.c		\
	  utils.c		\
	  ft_split.c	\
	  ft_strjoin.c	\
	  ft_strncmp.c	\
	  ft_strlcpy.c

HEADER = pipex.h

OBJ = $(SRC:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	gcc $(FLAGS) $(SRC) -o $(NAME)

%o:	%.c libft/*.c
	gcc $(FLAGS) -c $< -o $@

clean:
		 rm -rf $(OBJ) *.d

fclean:	 clean
		 rm -rf $(NAME) *.d

re:		 fclean all

.PHONY: clean fclean all re