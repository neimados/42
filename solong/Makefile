NAME = so_long

SRC = ./sources/so_long.c

OBJS = ${SRC:.c=.o}

MINILIBX = ./minilibx/
CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ./includes/so_long.h
		${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

$(NAME): ${OBJS}
		make -C ${MINILIBX}
		${CC} ${CFLAGS} -framework OpenGL -framework AppKit -o $@ $^ minilibx/libmlx.a

clean:
		make clean -C ${MINILIBX}
		${RM} ${OBJS}
 
fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re 