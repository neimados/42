NAME = philo

SRC = ./sources/ft_parsing.c ./sources/philo_utils.c ./sources/philo.c \
./sources/ft_threads.c ./sources/ft_cmds.c

OBJS = ${SRC:.c=.o}

CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ./includes/philo.h
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