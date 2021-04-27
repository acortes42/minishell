/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 09:31:42 by visv              #+#    #+#             */
/*   Updated: 2021/04/21 14:45:23 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <termios.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <stdarg.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>

# define ESCAPE				'\033'
# define ARROW_UP			"\033[A"
# define ARROW_DOWN			"\033[B"

# define BUFFER_SIZE		1000
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

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

typedef struct s_job
{
	struct s_job			*next;
	char					*command;
	t_process				*first_process;
	pid_t					pgid;
	char					notified;
	t_files_fd				std_fds;
}							t_job;

typedef struct s_abs_struct
{
	char					**env;
	int						num_args;
	int						lines_envp;
	char					*input;
	char					**parse_string;
	int						a;
	int						error;
	int						flag;
	int						ctrl_d_times;
	int						last_executed_process_status;
	t_job					*first_job;
	unsigned int			c_lflag;
	int						counter;
	int						history_lines;
	int						current_history_line;
}							t_abs_struct;

typedef struct s_expand_dollar
{
	t_abs_struct			*base;
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
int				assign_to_i_fd(int empty, char *fd);
int				assign_to_fd_helper(char c);
void			redirect_to_exit(t_abs_struct *base, int o_fd, int i_fd);
char			*ft_strdup(const char *s1);
char			*ft_strchr(const char *s, int c);
char			*ft_strcdup(const char *s1, int c);
int				get_next_line(int fd, char **line, t_abs_struct *base);
char			*ft_get_correct_line(int fd, char **line, int ret);
char			*ft_concat(char *line, char *bf, int *found_nl);
void			ft_shift_left(char *bf);
char			*ft_strjoin(char const *s1, char const *s2);
char			**ft_split(char const *s, char c);
void			ft_putstr(char *s);
void			ft_putnstr(char *s, size_t len);
void			ft_putnbr(int n);
int				ft_strcmp(const char *s1, const char *s2);
int				cd(t_abs_struct *base);
char			*ft_get_absolute_path(t_abs_struct *base, char *path);
int				echo(t_abs_struct *base, t_process *p);
int				ft_history(t_abs_struct *base);
int				ft_open_history(t_abs_struct *base, int mode);
void			ft_write_history_line(t_abs_struct *base);
int				ft_pwd(void);
int				ft_export(t_abs_struct *base, t_process *p);
int				ft_copy_env(t_abs_struct *base, char **envp);
int				ft_env(t_abs_struct *base);
int				ft_setenv(t_abs_struct *base, t_process *p);
void			ft_exit_minishell(t_abs_struct *base, int exit_code);
int				ft_unset(t_abs_struct *base, t_process *p);
int				ft_help(void);
void			handle_sigint(int sig);
int				ft_execute_command(t_abs_struct *base);
int				ft_execute_ctrl_d(t_abs_struct *base);
int				ft_init_minishell(t_abs_struct *base, char **envp);
void			clear_screen(void);
void			ft_show_prompt(t_abs_struct *base);

t_job			*ft_release_job(t_job *j);
void			ft_putstr_fd(char *s, int fd);
void			ft_update_status(t_abs_struct *base);

t_job			*ft_build_jobs(char *command);
t_job			*ft_build_job(char *command);
t_job			*ft_build_job_ctrl_d(char *command);
t_process		*ft_build_processes(char *expanded_cmd);
t_process		*ft_build_ctrl_d_process(void);
t_process		*ft_build_process(char *expanded_cmd);
int				set_redirections(t_abs_struct *base, t_process *p);
int				ft_output_add_redirection(t_abs_struct *base, char *redir, \
				int *redirected);
int				ft_output_redirection(t_abs_struct *base, char *redir, \
				int *redirected);
int				ft_input_redirection(t_abs_struct *base, char *redir, \
				int *redirected);
void			ft_set_pipes(t_process *previous, t_process *current);
void			ft_close_pipes(t_files_fd fd, t_process *previous, \
				t_process *current);
void			ft_configure_pipes(t_abs_struct *base, t_process *current);
int				ft_expand_process_cmd(t_abs_struct *base, t_process *p);

void			ft_launch_job(t_abs_struct *base, t_job *j);
void			ft_launch_process(t_abs_struct *base, t_process *p);
int				ft_execute_builtin(t_abs_struct *base, t_process *previous, \
				t_process *current);

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
char			**ft_array_dup(char **envp);
void			ft_array_release(char **envp);
size_t			ft_array_len(char **envp);
void			ft_array_slide_left(char **array);
char			*ft_getenv(char **env, char *key);
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
int				ft_isinteger(char *str);
int				ft_count_until_separator(char **str, int actual_arg);
int				ft_obtain_last(int fd, char **line);
void			ft_remove_quotes(char *field);
int				ft_expand_scape(char **res, char **cmd, size_t *pos);
char			*ft_extract_variable_name(char **cmd);
int				ft_expand_dollar(t_expand_dollar *d);
void			ft_execute_absolute_shell_command(t_abs_struct *base,
					char *cmd, t_process *p);
void			ft_execute_relative_shell_command(t_abs_struct *base,
					t_process *p);
int				ft_setlflag(int fd, int set_flag, unsigned int value);
int				classic_get_next(int fd, char **line);

int				ft_file_lines(char *file);
int				ft_file_lines_by_fd(int fd);
char 			*ft_get_file_line(char *file, int line);
char			*ft_get_file_line_by_fd(int fd, int line);
void			ft_clear_input(char **line);
void			ft_delete_chars(int len);

#endif
