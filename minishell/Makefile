NAME = minishell

SRC = ./srcs/minishell.c ./srcs/parsing/ft_parsing.c ./srcs/parsing/utils.c \
./srcs/parsing/ft_split.c ./srcs/parsing/ft_envp.c ./srcs/parsing/ft_itoa.c \
./srcs/parsing/ft_lst.c ./srcs/parsing/ft_args.c ./srcs/parsing/ft_cmds.c \
./srcs/parsing/ft_heredoc.c ./srcs/parsing/ft_parsing_utils.c \
./srcs/parsing/ft_vars.c \
./srcs/minishell.c ./srcs/parsing/ft_parsing.c ./srcs/parsing/utils.c \
./srcs/parsing/ft_split.c ./srcs/parsing/ft_envp.c  ./srcs/exec/k_exec.c ./srcs/exec/split.c ./srcs/exec/libft.c ./srcs/exec/libft_utils.c

OBJS = ${SRC:.c=.o}

CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ./includes/minishell.h Makefile
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