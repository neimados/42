NAME = libftprintf.a

SRC = ft_printf.c ft_printf_utils.c ft_printnbr.c \
ft_printchar.c ft_printnbru.c ft_itoa.c \
ft_printx.c ft_convbase.c ft_printp.c

OBJS = ${SRC:.c=.o}


CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror
 
%.o: %.c libft.h
		${CC} ${CFLAGS} -c -o $@ $<
 
$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}
 
all:	${NAME}
 
clean:
		${RM} ${OBJS}
 
fclean:	clean
		${RM} ${NAME}
 
re:		fclean all

bonus:	${OBJS}
		ar rcs ${NAME} ${OBJS}

.PHONY: all clean fclean re bonus