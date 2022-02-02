NAME = minishell

SRC = ./srcs/minishell.c ./srcs/parsing/ft_parsing.c ./srcs/parsing/utils.c \
./srcs/parsing/ft_split.c ./srcs/parsing/ft_envp.c ./srcs/parsing/ft_itoa.c \
./srcs/parsing/ft_lst.c ./srcs/parsing/ft_args.c ./srcs/parsing/ft_cmds.c \
./srcs/parsing/ft_heredoc.c ./srcs/parsing/ft_parsing_utils.c \
./srcs/parsing/ft_vars.c

OBJS = ${SRC:.c=.o}

CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g3

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