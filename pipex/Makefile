NAME = pipex

SRC = ./sources/ft_cmd.c ./sources/ft_split.c ./sources/pipex.c \
./sources/pipex_utils.c

OBJS = ${SRC:.c=.o}

CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ./includes/pipex.h
		${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

$(NAME): ${OBJS}
		${CC}  ${CFLAGS} -o $@ $^

clean:
		${RM} ${OBJS}
 
fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re 