UTILS 				= utils/ft_putnbr.c utils/ft_putstr.c utils/ft_split.c \
	utils/get_next_line.c utils/get_next_line_utils.c utils/ft_strcmp.c

SRCS_WITHOUT_MAIN	=  srcs/echo.c srcs/cd.c srcs/history.c \
	srcs/signals.c srcs/pwd.c srcs/env.c srcs/setenv.c srcs/vertical_line.c \
	srcs/ft_launch.c srcs/ft_export.c ${UTILS}
SRCS 				=  srcs/minishell.c ${SRCS_WITHOUT_MAIN}
		
CFLAGS				= -Wall -Wextra -Werror -I . -g  #-fsanitize=address
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
	@rm -f  srcs/*.o
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
	
${TESTS_IT}: 
	${MAKE} test_echo
	${MAKE} test_cd_pwd
	${MAKE} test_export_env
	${MAKE} test_unset
	${MAKE} test_exit
	${MAKE} test_semicolon
	${MAKE} test_quotes
	${MAKE} test_redirections

test_echo: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_echo > res/tests/outputs_it/test_echo_minishell); echo $? > res/tests/outputs_it/test_echo_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_echo > res/tests/outputs_it/test_echo_bash); echo $? > res/tests/outputs_it/test_echo_bash_output_code
	diff res/tests/outputs_it/test_echo_bash res/tests/outputs_it/test_echo_minishell 
	diff res/tests/outputs_it/test_echo_bash_output_code res/tests/outputs_it/test_echo_minishell_output_code
	rm res/tests/outputs_it/test_echo*

test_cd_pwd: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_cd > res/tests/outputs_it/test_cd_minishell); echo $? > res/tests/outputs_it/test_cd_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_cd > res/tests/outputs_it/test_cd_bash); echo $? > res/tests/outputs_it/test_cd_bash_output_code
	diff res/tests/outputs_it/test_cd_bash res/tests/outputs_it/test_cd_minishell 
	diff res/tests/outputs_it/test_cd_bash_output_code res/tests/outputs_it/test_cd_minishell_output_code
	rm res/tests/outputs_it/test_cd*

test_export_env: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_export_env > res/tests/outputs_it/test_export_env_minishell); echo $? > res/tests/outputs_it/test_export_env_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_export_env > res/tests/outputs_it/test_export_env_bash); echo $? > res/tests/outputs_it/test_export_env_bash_output_code
	diff res/tests/outputs_it/test_export_env_bash res/tests/outputs_it/test_export_env_minishell 
	diff res/tests/outputs_it/test_export_env_bash_output_code res/tests/outputs_it/test_export_env_minishell_output_code
	rm res/tests/outputs_it/test_export_env*

test_unset: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_unset > res/tests/outputs_it/test_unset_minishell); echo $? > res/tests/outputs_it/test_unset_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_unset > res/tests/outputs_it/test_unset_bash); echo $? > res/tests/outputs_it/test_unset_bash_output_code
	diff res/tests/outputs_it/test_unset_bash res/tests/outputs_it/test_unset_minishell 
	diff res/tests/outputs_it/test_unset_bash_output_code res/tests/outputs_it/test_unset_minishell_output_code
	rm res/tests/outputs_it/test_unset*

test_exit: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_exit -9 > res/tests/outputs_it/test_exit_minishell); echo $? > res/tests/outputs_it/test_exit_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_exit > res/tests/outputs_it/test_exit_bash); echo $? > res/tests/outputs_it/test_exit_bash_output_code
	diff res/tests/outputs_it/test_exit_bash res/tests/outputs_it/test_exit_minishell 
	diff res/tests/outputs_it/test_exit_bash_output_code res/tests/outputs_it/test_exit_minishell_output_code
	rm res/tests/outputs_it/test_exit*

test_semicolon: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_semicolon -9 > res/tests/outputs_it/test_semicolon_minishell); echo $? > res/tests/outputs_it/test_semicolon_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_semicolon > res/tests/outputs_it/test_semicolon_bash); echo $? > res/tests/outputs_it/test_semicolon_bash_output_code
	diff res/tests/outputs_it/test_semicolon_bash res/tests/outputs_it/test_semicolon_minishell 
	diff res/tests/outputs_it/test_semicolon_bash_output_code res/tests/outputs_it/test_semicolon_minishell_output_code
	rm res/tests/outputs_it/test_semicolon*

test_quotes: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_quotes -9 > res/tests/outputs_it/test_quotes_minishell); echo $? > res/tests/outputs_it/test_quotes_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_quotes > res/tests/outputs_it/test_quotes_bash); echo $? > res/tests/outputs_it/test_quotes_bash_output_code
	diff res/tests/outputs_it/test_quotes_bash res/tests/outputs_it/test_quotes_minishell 
	diff res/tests/outputs_it/test_quotes_bash_output_code res/tests/outputs_it/test_quotes_minishell_output_code
	rm res/tests/outputs_it/test_quotes*


test_redirections: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_redirections -9 > res/tests/outputs_it/test_redirections_minishell); echo $? > res/tests/outputs_it/test_redirections_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_redirections > res/tests/outputs_it/test_redirections_bash); echo $? > res/tests/outputs_it/test_redirections_bash_output_code
	diff res/tests/outputs_it/test_redirections_bash res/tests/outputs_it/test_redirections_minishell 
	diff res/tests/outputs_it/test_redirections_bash_output_code res/tests/outputs_it/test_redirections_minishell_output_code
	rm res/tests/outputs_it/test_redirections*


test_signals: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_signals -9 > res/tests/outputs_it/test_signals_minishell); echo $? > res/tests/outputs_it/test_signals_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_signals > res/tests/outputs_it/test_signals_bash); echo $? > res/tests/outputs_it/test_signals_bash_output_code
	diff res/tests/outputs_it/test_signals_bash res/tests/outputs_it/test_signals_minishell 
	diff res/tests/outputs_it/test_signals_bash_output_code res/tests/outputs_it/test_signals_minishell_output_code
	rm res/tests/outputs_it/test_signals*

test_ctrl_d: ${NAME}
	(timeout --preserve-status 3 ./minishell <res/tests/inputs/test_ctrl_d -9 > res/tests/outputs_it/test_ctrl_d_minishell 2> res/tests/outputs_it/test_ctrl_d_minishell_error); echo $? > res/tests/outputs_it/test_ctrl_d_minishell_output_code
	(timeout --preserve-status 3 /bin/bash <res/tests/inputs/test_ctrl_d > res/tests/outputs_it/test_ctrl_d_bash 2> res/tests/outputs_it/test_ctrl_d_bash_error); echo $? > res/tests/outputs_it/test_ctrl_d_bash_output_code
	diff res/tests/outputs_it/test_ctrl_d_bash res/tests/outputs_it/test_ctrl_d_minishell 
	diff res/tests/outputs_it/test_ctrl_d_bash_output_code res/tests/outputs_it/test_ctrl_d_minishell_output_code
	rm res/tests/outputs_it/test_ctrl_d*

