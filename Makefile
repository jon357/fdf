NAME		= fdf

SRC		= 	src/main.c			\
			src/draw.c			\
			src/init.c			\
			src/keybord.c		\
			src/tab.c			\

OBJ		= $(SRC:.c=.o)

FLAG		= -Wall -Wextra -Werror -g

RM		= rm -f

$(NAME):
		$(CC) $(FLAG) -Iinclude -g $(SRC) -Llib -lmlx -lXext -lX11 -lm -lft -o $@

all:		$(NAME)

clean:
		$(RM) $(OBJ) 

fclean:		clean
		$(RM) $(NAME)

re:		fclean all

.PHONY: all clean fclean re
