OBJS = minishell.c utils/ft_split.c utils/get_next_line.c utils/get_next_line_utils.c
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

