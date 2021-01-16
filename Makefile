UTILS 				= utils/ft_putnbr.c utils/ft_putstr.c utils/ft_split.c \
	utils/get_next_line.c utils/get_next_line_utils.c utils/ft_strcmp.c

SRCS_WITHOUT_MAIN	=  srcs/echo.c srcs/cd.c srcs/history.c \
	srcs/signals.c srcs/pwd.c srcs/env.c srcs/setenv.c srcs/vertical_line.c \
	${UTILS}
SRCS 				=  srcs/minishell.c ${SRCS_WITHOUT_MAIN}
		
CFLAGS				= -Wall -Wextra -Werror -I .
CFLAGS_DEBUG		= ${CFLAGS} -g -fsanitize=address
OBJS				= ${SRCS:.c=.o}
NAME				= minishell

# 
# Variables para compilado de tests (unitarios y de integración)
#
OBJS_WITHOUT_MAIN	:= ${SRCS_WITHOUT_MAIN:.c=.o}
CFLAGS_UNIT_TESTS	:= -I ./tests ${CFLAGS} -g -fsanitize=address 
LDFLAGS_UNIT_TESTS	:=
SRCS_UNIT_TESTS		:= \
	./tests/utils/ft_build_home.c \
	./tests/test_history.c \
	./tests/test_echo.c \
	./tests/tests.c
OBJS_UNIT_TESTS		:= ${SRCS_UNIT_TESTS:.c=.o} 
TESTS_IT_OUTPUTS	:= res/tests/outputs_it
TESTS_UT_OUTPUTS	:= res/tests/outputs_ut
TESTS_UT			:= check
TESTS_IT			:= check_it

all: ${NAME}

$(NAME): ${OBJS}
	${CC} -o ${NAME} ${CFLAGS} ${OBJS}

library: ${OBJS}
	@gcc -c ${CFLAGS} ${OBJS}
	@mkdir SourceFiles
	@mv *.o SourceFiles
	@ar rc ${NAME} ${COMP}

clean:
	@rm -f  *.o
	@rm -rdf SourceFiles
	${RM} ${OBJS_UNIT_TESTS} ${OBJS_WITHOUT_MAIN}
	${RM} -r ${TESTS_IT_OUTPUTS}/* ${TESTS_UT_OUTPUTS}/*

fclean: clean
	@rm -f *.o
	@rm -rdf SourceFiles
	@rm history.txt
	@touch history.txt
	@rm -f *.out
	@rm -f *.a
	${RM} minishell_check ${NAME}
	
test:	${OBJS}
	@gcc ${OBJS} && ./a.out

debug:	${OBJS}
	${CC} -o ${NAME} ${CFLAGS_DEBUG} ${OBJS}

re: fclean all

${TESTS_UT}: debug ${OBJS_UNIT_TESTS}
	${CC} ${CFLAGS_UNIT_TESTS} -o minishell_check ${OBJS_UNIT_TESTS} ${OBJS_WITHOUT_MAIN} ${LDFLAGS_UNIT_TESTS}
	./minishell_check > res/tests/outputs_ut/output 2> res/tests/outputs_ut/output_errors
	
${TESTS_IT}: test_echo

test_echo: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_echo > res/tests/outputs/test_echo_minishell); echo $? > res/tests/outputs/test_echo_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_echo > res/tests/outputs/test_echo_bash); echo $? > res/tests/outputs/test_echo_bash_output_code
	diff res/tests/outputs/test_echo_bash res/tests/outputs/test_echo_minishell 
	diff res/tests/outputs/test_echo_bash_output_code res/tests/outputs/test_echo_minishell_output_code
	rm res/tests/outputs/test_echo*