NAME = push_swap
NAME_CHECKER = checker

SRC = ./sources/push_swap.c ./sources/ft_stack.c ./sources/ft_parse.c \
./sources/ft_checkargs.c ./sources/ft_swap.c ./sources/ft_push.c \
./sources/ft_rotate.c ./sources/ft_reverse.c ./sources/ft_smallsort.c \
./sources/ft_sort_utils.c ./sources/ft_bigsort.c ./sources/ft_mediumsort.c \
./sources/ft_parse_utils.c

SRC_CHECKER = ./checkersrc/checker.c

OBJS = ${SRC:.c=.o}
OBJS_CHECKER = ${SRC_CHECKER:.c=.o}

LIBFT = ./libft/
CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ./includes/push_swap.h ./includes/checker.h
		${CC} ${CFLAGS} -c $< -o $@
 
$(NAME): ${OBJS}
		make -C $(LIBFT)
		${CC}  ${CFLAGS} -o $@ $^ libft/libft.a

$(NAME_CHECKER): ${OBJS_CHECKER}
		make -C $(LIBFT)
		${CC}  ${CFLAGS} -o $@ $^ libft/libft.a

all:	${NAME} $(NAME_CHECKER)

clean:
		make clean -C $(LIBFT)
		${RM} ${OBJS}
		${RM} ${OBJS_CHECKER}
 
fclean:	clean
		make fclean -C $(LIBFT)
		${RM} ${NAME}
		${RM} ${NAME_CHECKER}

re:		fclean all

.PHONY: all clean fclean re 