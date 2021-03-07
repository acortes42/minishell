#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1024
# define ANSI_COLOR_RED     "\x1b[31m"
# define ANSI_COLOR_GREEN   "\x1b[32m"
# define ANSI_COLOR_YELLOW  "\x1b[33m"
# define ANSI_COLOR_BLUE    "\x1b[34m"
# define ANSI_COLOR_MAGENTA "\x1b[35m"
# define ANSI_COLOR_CYAN    "\x1b[36m"
# define ANSI_COLOR_RESET   "\x1b[0m"

# include <sys/wait.h>   
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <stdarg.h>
# include <errno.h>
# include <signal.h>
# include <limits.h>


typedef struct s_files_fd
{
	int infile;
    int outfile;
	int errfile;
}				t_files_fd;

/* A process is a single process.  */
typedef struct s_process
{
  struct s_process	*next;       /* next process in pipeline */
  char				**argv;                /* for exec */
  char				**redirs;
  pid_t				pid;                  /* process ID */
  char				completed;             /* true if process has completed */
  char				stopped;               /* true if process has stopped */
  int				status;                 /* reported status value */
  int				pipe[2];
} t_process;


/* A job is a pipeline of processes.  */

typedef struct		s_job
{
	struct s_job	*next;           /* next active job */
	char			*command;              /* command line, used for messages */
	t_process		*first_process;     /* list of processes in this job */
	pid_t			pgid;                 /* process group ID */
	char			notified;              /* true if user told about stopped job */
	//struct termios tmodes;      /* saved terminal modes */
	t_files_fd		std_fds;
} 					t_job;

typedef struct		abs_struct
{
	char    		**env;
	int     		num_args;
	int     		lines_envp;
	char	string[1024];
	char    **parseString;
	int     actual_argument;
	int     error;
	int     		flag;
	int				ctrl_d_times;
	t_process		*last_executed_process;
	t_job			*first_job;
}                   abs_struct;    

char				*ft_strdup(const char *s1);
char				*ft_strchr(char *str, int c);
char				*ft_strcdup(const char *s1, int c);
int					get_next_line(int fd, char **line);
char				*ft_strjoin(char const *s1, char const *s2);
char				**ft_split(char const *s, char c);
void				ft_putstr(char *s);
void				ft_putnstr(char *s, size_t len);
void				ft_putnbr(int n);
int					ft_strcmp(const char *s1, const char *s2);
int    				cd(abs_struct *base);
char				*ft_get_absolute_path(abs_struct *base, char *path);
int    				echo(abs_struct *base);
int    				ft_history();
int    				ft_pwd();
int    				ft_launch(abs_struct *base);
int					ft_export(abs_struct *base, t_process *p);
int    				ft_copy_env(abs_struct *base, char **envp);
int    				ft_env(abs_struct *base);
int    				ft_setenv(abs_struct *base, t_process *p);
void				ft_exit_minishell(abs_struct *base, int exit_code);
int    				ft_unset(abs_struct *base, t_process *p);
int    				ft_help();
int    				vertical_line(abs_struct *base); 
void				handle_sigint(int sig);
int					ft_execute_command(abs_struct *base);
int					ft_execute_ctrl_d(abs_struct *base);
int					ft_init_minishell(abs_struct *base, char **envp);
void				clearScreen();
void		    	ft_show_prompt(abs_struct *base);

t_job				*ft_release_job(t_job *j);
void				ft_putstr_fd(char *s, int fd);
int					ft_job_is_completed(t_job *j);
int					ft_job_is_stopped(t_job *j);
void				ft_format_job_info(t_job *j, const char *status);
void				ft_do_job_notification(t_job *j);
void				ft_mark_job_as_running(t_job *j);
void				ft_update_status(abs_struct *base);

t_job				*ft_build_jobs(abs_struct *base, char *command);
t_job				*ft_build_job(abs_struct *base, char *command);
t_process			*ft_build_processes(char *expanded_cmd);
t_process			*ft_build_ctrl_d_process(void);
t_process			*ft_build_process(char *expanded_cmd);
int					set_redirections(abs_struct *base, t_process *p);

void				ft_launch_job(abs_struct *base, t_job *j);
void            	ft_launch_process(abs_struct *base, t_process *previous, t_process *current);
int         		ft_execute_builtin(abs_struct *base, t_process *p);

void				ft_release_base(abs_struct *base);
void				ft_release_jobs(t_job *job);
t_process			*ft_release_process(t_process *p);
int					ft_set_default_signals();
void				forked_process_signal_handler(int sig);
void				dup_std_fds(t_files_fd *fds);
void				restore_std_fds(t_files_fd *fds);
int					ft_extract_redirections_from_argv(t_process *p);

size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strlcat_paths(char *prefix_path, const char *relative_path);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strnlen(const char *s, size_t max);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
int					ft_array_add(char ***array, int *array_len, char *value);
char				**ft_array_dup(char **envp);
void				ft_array_release(char **envp);
size_t				ft_array_len(char **envp);
void				ft_array_slide_left(char **array);
char				*ft_getenv(char **env, char *key);
size_t				ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
void				*ft_memset(void *b, int c, size_t len);
int					ft_isempty(const char *s);
int					ft_isspace(int s);
int					ft_atoi(const char *nptr);
char				*ft_itoa(int n2);
int					ft_isdigit(int c);
void				*ft_calloc(size_t nmemb, size_t size);
void				ft_bzero(void *s, size_t n);
char				*ft_trim(char *str);
char				*ft_split_shell(char **str);
char				*ft_split_shell_by(char **str, char *separator);
int					ft_isinteger(char *str);
int					ft_count_words_until_separator(char **str, int actual_arg);

#endif
