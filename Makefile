#PRINT = printf/ft_all_values_to_start.c printf/ft_super_function.c printf/ft_x.c printf/ft_big_x.c  printf/ft_c.c printf/ft_d.c printf/ft_i.c \
		printf/ft_my_args.c printf/ft_new_me.c printf/ft_p.c printf/ft_printf.c printf/ft_rest.c printf/ft_restart_values.c printf/ft_s.c \
		printf/ft_u.c printf/ft_write_and_sum.c printf/ft_convert_to_hex.c printf/ft_functions1.c printf/ft_functions2.c printf/ft_functions3.c

GETNEXT = utils/ft_split.c utils/get_next_line.c utils/get_next_line_utils.c

SRCS_MINISHELL_WITHOUT_MAIN	:= srcs/echo.c srcs/cd.c srcs/history.c srcs/signals.c srcs/pwd.c \
		srcs/env.c srcs/setenv.c ${GETNEXT} #${PRINT}
OBJS =  srcs/minishell.c ${SRCS_MINISHELL_WITHOUT_MAIN}
OBJS_MINISHELL_WITHOUT_MAIN	:= ${SRCS_MINISHELL_WITHOUT_MAIN:.c=.o}

CFLAGS = -Wall -Wextra -Werror -I ./printf -I . -I ./libft
COMP = ${OBJS:.c=.o}
NAME = minishell

CFLAGS_TESTS		:= -I ./tests ${CFLAGS} -g -fsanitize=address 
LDFLAGS 			:= -L ./printf -lftprintf -L ./libft -lft 

SRCS_TESTS			:= \
	./tests/utils/ft_build_home.c \
	./tests/test_history.c \
	./tests/tests.c
OBJS_TESTS			:= ${SRCS_TESTS:.c=.o} 
TESTS				:= check

${TESTS}: ${NAME} ${OBJS_TESTS}
	${CC} ${CFLAGS_TESTS} -o minishell_check ${OBJS_TESTS} ${OBJS_MINISHELL_WITHOUT_MAIN} ${LDFLAGS}
	./minishell_check

all: ${NAME}

$(NAME): ${COMP}
	${MAKE} -C ./libft
	${MAKE} -C ./printf
#	@gcc -c ${CFLAGS} ${OBJS}
#	@mv *.o srcs
#	@ar rc ${NAME} ${COMP}
	@gcc ${CFLAGS} -o ${NAME} ${OBJS} ${LDFLAGS}

clean:
	@rm -f  *.o
	${MAKE} -C printf clean
	${RM} ./srcs/*.o *.o ${OBJS_TESTS} ${COMP}

fclean: clean
	@rm -f *.o
	@rm -f *.out
	@rm -f *.a
	${MAKE} -C printf fclean
	${RM} ${NAME} ${TESTS}
	
test:	${OBJS} minishell.h
	@gcc ${OBJS} && ./a.out

debug:	${OBJS} minishell.h
	@gcc -g ${CFLAGS} ${OBJS}

re: fclear all

