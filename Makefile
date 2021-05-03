UTILS 				= utils/ft_putnbr.c utils/ft_putstr.c utils/ft_strchr.c \
	utils/ft_split.c utils/ft_strcmp.c utils/ft_strdup.c utils/ft_strjoin.c \
	utils/get_next_line_visv.c utils/get_next_line_utils_visv.c \
	utils/ft_strlcpy.c utils/ft_memcmp.c utils/ft_array_dup.c \
	utils/ft_array_release.c utils/ft_array_len.c utils/ft_strlen.c \
	utils/ft_memset.c utils/ft_isempty.c utils/ft_isspace.c \
	utils/ft_strnlen.c utils/ft_strlcat.c utils/ft_get_absolute_path.c \
	utils/ft_memcpy.c utils/ft_release_base.c utils/ft_isdigit.c \
	utils/ft_atoi.c utils/ft_launch_process.c utils/ft_launch_job.c \
	utils/ft_strncmp.c utils/ft_output_add_redirection.c \
	utils/ft_output_redirection.c utils/ft_input_redirection.c \
	utils/ft_putstr_fd.c utils/ft_release_jobs.c utils/ft_release_job.c \
	utils/ft_itoa.c utils/ft_calloc.c utils/ft_build_jobs.c \
	utils/ft_bzero.c utils/ft_execute_builtin.c utils/ft_build_job.c \
	utils/ft_build_processes.c utils/ft_build_process.c utils/ft_trim.c \
	utils/ft_split_shell.c utils/ft_release_process.c utils/ft_array_add.c \
	utils/redirections.c utils/ft_array_slide_left.c \
	utils/ft_set_default_signals.c utils/ft_isinteger.c utils/std_fds.c	\
	utils/ft_extract_redirections_from_argv.c \
	utils/ft_count_words_until_separator.c utils/ft_expand_process_cmd.c \
	utils/pipes.c utils/ft_remove_quotes.c \
	utils/ft_expand_process_cmd_utils.c \
	utils/ft_execute_absolute_shell_command.c \
	utils/ft_execute_relative_shell_command.c utils/ft_setlflag.c \
	utils/ft_classic_get_next.c utils/ft_get_count_line.c \
	utils/ft_get_correct_line.c utils/ft_file_lines.c \
	utils/ft_get_file_line.c utils/ft_open_history.c \
	utils/ft_clear_input.c utils/ft_write_history_line.c \
	utils/get_next_line_utils.c utils/load_history_commands.c \
	utils/process_escape_sequences.c utils/process_csi_sequences.c

SRCS_WITHOUT_MAIN	=  srcs/ft_exit_minishell.c srcs/clear_screen.c \
	srcs/ft_execute_ctrl_d.c srcs/echo.c srcs/cd.c \
	srcs/history.c srcs/signals.c srcs/pwd.c srcs/env.c srcs/setenv.c \
	srcs/ft_export.c srcs/ft_getenv.c  srcs/setenv_aux.c\
	srcs/ft_init_minishell.c srcs/ft_show_prompt.c srcs/ft_expand_env_value.c ${UTILS}

SRCS 				=  srcs/minishell.c ${SRCS_WITHOUT_MAIN}

CFLAGS				= -Wall -Wextra -Werror -I . -g -fsanitize=address
CFLAGS_DEBUG		= ${CFLAGS} -g -fsanitize=address
OBJS				= ${SRCS:.c=.o}
NAME				= minishell

CC					= gcc
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

keyboard: fclean
	${CC} -o test_keyboard ${CFLAGS} tests/keyboard.c

pipes: fclean
	${CC} -o pipes ${CFLAGS} tests/pipes_redirs.c

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
	${RM} tests/pipes_redirs.o
	${RM} ${OBJS_UNIT_TESTS} ${OBJS_WITHOUT_MAIN}
	${RM} -r ${TESTS_IT_OUTPUTS}/* ${TESTS_UT_OUTPUTS}/*

fclean: clean
	@rm -f *.o
	@rm -rdf SourceFiles
	@rm -f history.txt
	@touch history.txt
	@rm -f history_visv.txt
	@touch history_visv.txt
	@rm -f *.out
	@rm -f *.a
	${RM} ${NAME}
	${RM} pipes redirection_redirected_output test_keyboard
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

