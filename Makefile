UTILS = utils/ft_putnbr.c utils/ft_putstr.c utils/ft_split.c utils/get_next_line.c \
		utils/get_next_line_utils.c utils/ft_strcmp.c

OBJS =  srcs/minishell.c srcs/echo.c srcs/cd.c srcs/history.c srcs/signals.c srcs/pwd.c \
		srcs/env.c srcs/setenv.c srcs/vertical_line.c srcs/ft_launch.c srcs/ft_export.c ${UTILS}
		
CFLAGS = -Wall -Wextra -Werror
COMP = ${OBJS: .c =.o}
NAME = minishell.a

all: ${NAME}

$(NAME): ${OBJS} minishell.h
	@gcc -c ${CFLAGS} ${OBJS}
	@mkdir SourceFiles
	@mv *.o SourceFiles
	@ar rc ${NAME} ${COMP}
clean:
	@rm -f  *.o
	@rm -rdf SourceFiles
fclean: clean
	@rm -f *.o
	@rm -rdf SourceFiles
	@rm history.txt
	@touch history.txt
	@rm -f *.out
	@rm -f *.a
	
test:	${OBJS} minishell.h
	@gcc ${OBJS} && ./a.out

debug:	${OBJS} minishell.h
	@gcc -g ${CFLAGS} ${OBJS}

re: fclear all

