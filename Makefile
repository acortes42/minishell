UTILS = utils/ft_putnbr.c utils/ft_putstr.c utils/ft_split.c utils/get_next_line.c \
		utils/get_next_line_utils.c utils/ft_strcmp.c

OBJS =  srcs/minishell.c srcs/echo.c srcs/cd.c srcs/history.c srcs/signals.c srcs/pwd.c \
		srcs/env.c srcs/setenv.c srcs/vertical_line.c ${PRINT} ${UTILS}
		
CFLAGS = -Wall -Wextra -Werror -I .
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
	${RM} ${OBJS_TESTS}

fclean: clean
	@rm -f *.o
	@rm -rdf SourceFiles
	@rm history.txt
	@touch history.txt
	@rm -f *.out
	@rm -f *.a
	${RM} minishell_check
	
test:	${OBJS} minishell.h
	@gcc ${OBJS} && ./a.out

debug:	${OBJS} minishell.h
	@gcc -g ${CFLAGS} ${OBJS}

re: fclean all

# Revisar el compilado de los fuentes de minishell
OBJS_MINISHELL_WITHOUT_MAIN	:=   SourceFiles/echo.o SourceFiles/cd.o SourceFiles/history.o SourceFiles/signals.o SourceFiles/pwd.o \
		SourceFiles/env.o SourceFiles/setenv.o SourceFiles/vertical_line.o \
		SourceFiles/ft_putnbr.o SourceFiles/ft_putstr.o SourceFiles/ft_split.o SourceFiles/get_next_line.o \
		SourceFiles/get_next_line_utils.o SourceFiles/ft_strcmp.o
CFLAGS_TESTS		:= -I ./tests ${CFLAGS} -g -fsanitize=address 
LDFLAGS 			:=
SRCS_TESTS			:= \
	./tests/utils/ft_build_home.c \
	./tests/test_history.c \
	./tests/tests.c
OBJS_TESTS			:= ${SRCS_TESTS:.c=.o} 
TESTS				:= check

${TESTS}: ${NAME} ${OBJS_TESTS}
	${CC} ${CFLAGS_TESTS} -o minishell_check ${OBJS_TESTS} ${OBJS_MINISHELL_WITHOUT_MAIN} ${LDFLAGS}
	./minishell_check
	
