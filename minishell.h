/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 09:31:42 by visv              #+#    #+#             */
/*   Updated: 2021/05/16 18:42:16 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <stdio.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <stdarg.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>

# define REDIRECTIONS_MINIMUM_FD	11
# define MAX_FD						4096
# define TAB_SPACES					4
# define CTRL_C						'\x3'
# define CTRL_D						'\x4'
# define DEL						'\x7F'
# define ESCAPE						'\033'
# define FE_ESCAPE_START			'\x40'
# define FE_ESCAPE_END				'\x5F'
# define CSI_ESCAPE					"\033["
# define ARROW_UP					"\033[A"
# define ARROW_DOWN					"\033[B"
# define CLEAR_LINE					"\033[2K"

# define ANSI_COLOR_RED     		"\x1b[31m"
# define ANSI_COLOR_GREEN   		"\x1b[32m"
# define ANSI_COLOR_YELLOW  		"\x1b[33m"
# define ANSI_COLOR_BLUE    		"\x1b[34m"
# define ANSI_COLOR_MAGENTA 		"\x1b[35m"
# define ANSI_COLOR_CYAN    		"\x1b[36m"
# define ANSI_COLOR_RESET   		"\x1b[0m"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef struct s_files_fd
{
	int						infile;
	int						outfile;
	int						errfile;
}							t_files_fd;

typedef struct s_process
{
	struct s_process		*prev;
	struct s_process		*next;
	char					**argv;
	char					**redirs;
	pid_t					pid;
	char					completed;
	char					stopped;
	int						ctrl_d;
	int						status;
	int						pipe[2];
}							t_process;

typedef struct s_env_update
{
	int						changed_dir;
	t_process				*p;
	char					*old_pwd;
	char					*pwd;
	char					*home;
}							t_env_update;

typedef struct s_job
{
	struct s_job			*next;
	char					*command;
	t_process				*first_process;
	pid_t					pgid;
	char					notified;
}							t_job;

typedef struct s_abs_struct
{
	char					**env;
	int						num_args;
	int						lines_envp;
	char					*input;
	char					input_bf[BUFFER_SIZE];
	char					**parse_string;
	int						a;
	int						flag;
	int						ctrl_d_times;
	char					*arrow_up;
	char					*arrow_down;
	t_job					*first_job;
	t_process				*current_process;
	unsigned int			c_lflag;
	int						counter;
	char					**history;
	int						history_lines;
	int						current_history_line;
	char					*last_history_command;
	t_files_fd				std_fds;
}							t_abs_struct;

typedef struct s_expand_dollar
{
	t_abs_struct			*base;
	t_process				*proc;
	char					*expanded;
	size_t					expanded_len;
	size_t					pos;
	char					*cmd;
	char					quote;
	char					single_quote;
	int						scape;
}							t_expand_dollar;

typedef struct s_expand_dollar_internal
{
	char					*key;
	char					*variable;
	char					*tmp;
	size_t					key_len;
	size_t					variable_len;
}							t_expand_dollar_internal;

int				ft_check_home2(char *home);
int				ft_check_home(char *home);
int				give_int(int d);
int				ft_get_redirection_fd(char *redirection, int flags,
					mode_t mode, int default_fd);
int				ft_get_fd(char *redirection, int default_fd);
int				assign_to_fd_helper(char c);
void			redirect_to_exit(int o_fd, int i_fd);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
char			**ft_strstr_in_array(const char **array, char *tgt);
char			*ft_strstr(const char *s, char *tgt);
char			*ft_strcdup(const char *s1, int c);
int				get_next_line(int fd, char **line, t_abs_struct *base);
char			*ft_concat(char *line, char *bf, int *found_nl);
void			ft_shift_left(char *bf);
void			ft_shift_left_bytes(char *bf, int bytes);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
char			**ft_split_key_value_pair(char const *s, char c);
void			ft_putstr(char *s);
void			ft_putnstr(char *s, size_t len);
void			ft_putnbr(int n);
int				ft_strcmp(const char *s1, const char *s2);
int				cd(t_process *process);
int				go_home(t_process *p);
int				go_oldpwd(t_process *p);
void			perform_chdir_and_environment_update(t_process *p, char *home);
char			*ft_get_absolute_path(t_abs_struct *base, char *path);
int				ft_echo(t_process *p);
int				ft_history(t_abs_struct *base);
int				ft_open_history(t_abs_struct *base, int mode);
void			ft_write_history_line(t_abs_struct *base);
void			load_previous_history_command(t_abs_struct *base, char **line,
					char *bf);
void			load_next_history_command(t_abs_struct *base, char **line,
					char *bf);
int				ft_pwd(void);
void			ft_export(t_abs_struct *base, t_process *p);
int				ft_copy_env(t_abs_struct *base, char **envp);
int				ft_env(t_abs_struct *base, t_process *p);
int				ft_setenv(t_abs_struct *base, char *arg);
void			ft_exit_minishell(int exit_code);
int				ft_unset(t_abs_struct *base, t_process *p);
int				ft_help(void);
void			signal_handler(int sig);
int				ft_execute_command(t_abs_struct *base);
int				ft_execute_ctrl_d(t_abs_struct *base);
int				ft_init_minishell(t_abs_struct *base, char **envp);
void			ft_init_history(t_abs_struct *base);
void			ft_clear_screen(void);
void			ft_show_prompt(t_abs_struct *base);
void			enableRawMode(void);

t_job			*ft_release_job(t_job *j);
void			ft_putstr_fd(char *s, int fd);
void			ft_update_status(t_abs_struct *base);

t_job			*ft_build_jobs(char *command);
t_job			*ft_build_job(char *command);
t_job			*ft_build_job_ctrl_d(void);
t_process		*ft_build_processes(char *expanded_cmd);
t_process		*ft_build_ctrl_d_process(void);
t_process		*ft_build_process(char *expanded_cmd);
int				set_redirections(t_abs_struct *base, t_process *p);
int				ft_output_add_redirection(t_abs_struct *base, char *redir, \
					int *redirected);
int				ft_output_redirection(char *redir, int *redirected);
int				ft_input_redirection(char *redir, int *redirected);
void			ft_set_pipes(t_process *previous, t_process *current);
void			ft_close_pipes(t_process *previous, t_process *current);
int				ft_configure_pipes(t_process *current);
int				ft_expand_process_cmd(t_abs_struct *base, t_process *curr);
void			ft_expand_tilde(t_expand_dollar *d);

void			ft_launch_job(t_abs_struct *base, t_job *j);
void			ft_launch_process(t_abs_struct *base, t_process *p);
int				ft_execute_builtin(t_abs_struct *base, t_process *current);

void			ft_release_base(t_abs_struct *base);
void			ft_release_jobs(t_job *job);
t_process		*ft_release_process(t_process *p);
int				ft_set_default_signals(void);
void			forked_process_signal_handler(int sig);
void			dup_std_fds(t_files_fd *fds);
void			restore_std_fds(t_files_fd *fds);
int				ft_extract_redirections_from_argv(t_process *p);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strlcat_paths(char *prefix_path, const char *relative_path);
size_t			ft_strlcpy(char *dst, const char *src, size_t size);
size_t			ft_strnlen(const char *s, size_t max);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			*ft_memcpy(void *dest, const void *src, size_t n);
int				ft_array_add(char ***array, int *array_len, char *value);
int				ft_array_delete_pos(char ***array, int *array_len, int pos);
int				field_contains_redirs(char *field);
int				ft_array_update(char ***array, int *array_len, char *key,
					char *value);
char			**ft_array_dup(char **envp);
char			**ft_array_dup_without(char **env, size_t len_env,
					char *not_dup);
void			ft_array_release(char **envp);
size_t			ft_array_len(char **envp);
void			ft_array_slide_left(char **array);
int				is_env_valid_argument(char *arg);
char			*ft_getenv(char **env, char *key);
int				ft_search_env(char **env, char *key);
char			*expand_env_value(char **envp, char *env_value);
size_t			ft_strlen(const char *s);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
void			*ft_memset(void *b, int c, size_t len);
int				ft_isempty(const char *s);
int				ft_isspace(int s);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n2);
int				ft_isdigit(int c);
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_bzero(void *s, size_t n);
char			*ft_trim(char *str);
char			*ft_split_shell(char **str);
char			*ft_split_shell_by(char **str, char *separator);
char			*ft_split_shell_process(char **str);
int				check_base_syntatic_errors(char *cmd);
char			*get_first_non_empty_arg(char **args);
char			**get_first_non_empty_arg_pos(char **args);
int				ft_isinteger(char *str);
int				ft_count_until_separator(char **str, int actual_arg);
void			ft_remove_quotes(char *field);
char			*ft_extract_variable_name(char **cmd);
int				ft_expand_scape(t_expand_dollar *d);
int				ft_expand_dollar(t_expand_dollar *d);
void			ft_expand_quote(t_expand_dollar *d);
void			ft_print_last_process_status(t_expand_dollar *d);
void			ft_execute_absolute_shell_command(t_abs_struct *base,
					char *cmd, t_process *p);
void			ft_execute_relative_shell_command(t_abs_struct *base,
					t_process *p);
int				ft_setlflag(int fd, int set_flag, unsigned int value);
int				classic_get_next(int fd, char **line, int clean_buffer);
int				ft_isascii(int c);
void			ft_borrow_char(int x, char **line, char *bf);

int				ft_file_lines(char *file);
int				ft_file_lines_by_fd(int fd);
char			*ft_get_file_line(char *file, int line);
char			*ft_get_file_line_by_fd(int fd, int line);
void			ft_clear_input(char **line);
void			ft_delete_chars(int len);
int				process_escape_sequences(char *bf, char **line,
					t_abs_struct *base);
int				process_csi_escape_sequence(char *bf, char **line,
					t_abs_struct *base);
void			ft_update_environment_pwds(char *old_pwd, char *pwd);
int				ft_get_first_fd_available_between(int minimum, int maximum);
char			*ft_strtrim(char const *s1, char const *set);
void			ft_delete_existing_key(t_abs_struct *base, char *key);
char			*expand(t_abs_struct *base, t_process *curr,
					char *cmd);
int				exists_non_digits_chars(char *exit_code);
void			ft_wait_for_childs(t_job *j);
int				ft_adjust_exit_value(int exit_code);
void			ft_wait_for_process(t_process *curr);
int				ft_isbuiltin(t_process *p);

t_abs_struct	g_base;
#endif
