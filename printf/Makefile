NAME = libftprintf.a

SRC = ft_printf.c ft_printf_utils.c ft_printnbr.c ft_printtchar.c ft_printtnbru.c ft_itoa.c ft_printx.c ft_convbase.c

OBJS = ${SRC:.c=.o}

CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror
 
.c.o:
		${CC} ${CFLAGS} -g -c $< -o ${<:.c=.o}
 
$(NAME): ${OBJS}
		ar rcs ${NAME} ${OBJS}
 
all:    ${NAME}
 
clean:
		${RM} ${OBJS}
 
fclean:	clean
		${RM} ${NAME}
 
re:		fclean all

.PHONY: .c.o all clean fclean re