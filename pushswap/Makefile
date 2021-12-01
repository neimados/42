NAME = push_swap

SRC = ./sources/push_swap.c ./sources/ft_stack.c ./sources/ft_parse.c \
./sources/ft_checkargs.c ./sources/ft_swap.c ./sources/ft_push.c \
./sources/ft_rotate.c ./sources/ft_reverse.c ./sources/ft_sort.c \
./sources/ft_sort_utils.c ./sources/ft_bigsort.c

OBJS = ${SRC:.c=.o}

LIBFT = ./libft/
CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror
 
%.o: %.c ./includes/push_swap.h
		${CC} ${CFLAGS} -c $< -o $@ 
 
$(NAME): ${OBJS}
		make -C $(LIBFT)
		${CC}  ${CFLAGS} -o $@ $^ libft/libft.a
 
all:	${NAME}
 
clean:
		make clean -C $(LIBFT)
		${RM} ${OBJS}
 
fclean:	clean
		make fclean -C $(LIBFT)
		${RM} ${NAME}
 
re:		fclean all

bonus:	${OBJS}
		ar rcs ${NAME} ${OBJS}

.PHONY: all clean fclean re bonus