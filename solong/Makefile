NAME = so_long

SRC = ./sources/so_long.c ./sources/ft_check_map.c ./sources/ft_parse_map.c \
./sources/get_next_line.c ./sources/get_next_line_utils.c ./sources/ft_print_map.c \
./sources/so_long_utils.c ./sources/ft_move.c ./sources/ft_init.c ./sources/ft_free.c

OBJS = ${SRC:.c=.o}

LIBFT = ./libft/
MINILIBX = ./minilibx/
CC		= gcc
RM		= rm -f
CFLAGS = -Wall -Wextra -Werror

%.o: %.c ./includes/so_long.h
		${CC} ${CFLAGS} -c $< -o $@

all:	${NAME}

$(NAME): ${OBJS} 
		make -C $(LIBFT)
		make -C ${MINILIBX}
		${CC} ${CFLAGS} -framework OpenGL -framework AppKit -o $@ $^ minilibx/libmlx.a libft/libft.a

clean:
		make clean -C $(LIBFT)
		make clean -C ${MINILIBX}
		${RM} ${OBJS}
 
fclean:	clean
		make fclean -C $(LIBFT)
		${RM} ${NAME}

re:		fclean all

.PHONY: all clean fclean re