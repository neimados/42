NAME = minishell

SRC = ./srcs/minishell.c ./srcs/parsing/ft_parsing.c ./srcs/parsing/utils.c \
./srcs/parsing/ft_split.c ./srcs/parsing/ft_envp.c ./srcs/parsing/ft_itoa.c \
./srcs/parsing/ft_lst.c ./srcs/parsing/ft_args.c ./srcs/parsing/ft_cmds.c \
./srcs/parsing/ft_heredoc.c ./srcs/parsing/ft_parsing_utils.c \
./srcs/parsing/ft_vars.c ./srcs/parsing/utils2.c ./srcs/parsing/ft_split_utils.c \
./srcs/minishell.c ./srcs/parsing/ft_parsing.c ./srcs/parsing/utils.c \
./srcs/parsing/ft_split.c ./srcs/parsing/ft_envp.c  ./srcs/exec/k_exec.c \
./srcs/exec/split.c ./srcs/exec/libft.c ./srcs/exec/libft_utils.c \
./srcs/builtins/ft_echo.c ./srcs/builtins/ft_env.c ./srcs/builtins/ft_exit.c \
./srcs/builtins/ft_pwd.c ./srcs/builtins/ft_export.c ./srcs/builtins/ft_unset.c \
./srcs/builtins/ft_cd.c ./srcs/signals/ft_signals.c \
./srcs/parsing/get_next_line.c ./srcs/parsing/get_next_line_utils.c \
./srcs/signals/ft_terminal.c ./srcs/parsing/ft_vars_utils.c ./srcs/parsing/ft_heredoc_utils.c \
./srcs/parsing/ft_cmds_utils.c ./srcs/parsing/ft_args_utils.c

OBJS = ${SRC:.c=.o}

CC		= gcc
CFLAGS = -Wall -Wextra -Werror

READLINE_LIB	=	-L$(shell brew --prefix readline)/lib
READLINE_INC	=	-I$(shell brew --prefix readline)/include

%.o: %.c ./includes/minishell.h Makefile
		${CC} ${CFLAGS} ${READLINE_INC} -c $< -o $@

all:	${NAME}

$(NAME): ${OBJS}
		${CC} ${CFLAGS} -lreadline ${READLINE_LIB} ${READLINE_INC} -o $@ $^

clean:
		${RM} ${OBJS}
 
fclean:	clean
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re 