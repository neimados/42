NAME = minishell

SRC = ./srcs/minishell.c ./srcs/parsing/ft_parsing.c ./srcs/parsing/utils.c \
./srcs/parsing/ft_split.c ./srcs/parsing/ft_envp.c

OBJS = ${SRC:.c=.o}

CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ./includes/minishell.h
		${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

$(NAME): ${OBJS}
		${CC} ${CFLAGS} -lreadline -o $@ $^

clean:
		${RM} ${OBJS}
 
fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re 