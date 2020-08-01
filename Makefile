OBJS = minishell.c echo.c utils/ft_split.c utils/get_next_line.c utils/get_next_line_utils.c \
		printf/ft_all_values_to_start.c printf/ft_super_function.c printf/ft_x.c printf/ft_big_x.c  printf/ft_c.c printf/ft_d.c printf/ft_i.c \
		printf/ft_my_args.c printf/ft_new_me.c printf/ft_p.c printf/ft_printf.c printf/ft_rest.c printf/ft_restart_values.c printf/ft_s.c \
		printf/ft_u.c printf/ft_write_and_sum.c printf/ft_convert_to_hex.c printf/ft_functions1.c printf/ft_functions2.c printf/ft_functions3.c
CFLAGS = -Wall -Wextra -Werror
COMP = ${OBJS: .c =.o}
NAME = minishell.a

all: ${NAME}

$(NAME): ${OBJS} minishell.h
	@gcc ${CFLAGS} -c ${OBJS}
	@ar rc ${NAME} ${COMP}
clean:
	@rm -f  *.o
fclean: clean
	@rm -f *.o
	@rm -f *.out
	@rm -f *.a
	
test:	${OBJS} minishell.h
	@gcc ${OBJS} && ./a.out

debug:	${OBJS} minishell.h
	@gcc -g ${CFLAGS} ${OBJS}

re: fclear all

