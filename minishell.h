#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE 1024

# include <stdio.h>
# include <string.h>
# include <fcntl.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <ctype.h>
# include <stdarg.h>
# include <signal.h>
# include <limits.h>
# include <sys/wait.h>   


typedef struct      abs_struct
{
    char    **env;
    char    string[1024];
    char    **parseString;
    char    **valid_str;
    int     exceptionNum;
    int     num_args;
    int     lines_envp;
    int     actual_argument;
    int     flag;
    int     error;
}                   abs_struct;    

char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strchr(char *str, int c);
char	*ft_strcdup(const char *s1, int c);
int		get_next_line(int fd, char **line);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
void	ft_putstr(char *s);
void	ft_putnbr(int n);
int		ft_strcmp(const char *s1, const char *s2);
int     cd(abs_struct *base);
int     echo(abs_struct *base);
int     ft_history();
int     ft_pwd();
int     ft_launch(abs_struct *base);
int		ft_export(abs_struct *base);
int     ft_copy_env(abs_struct *base, char **envp);
int     ft_env(abs_struct *base);
int     ft_setenv(abs_struct *base);
int     ft_find_and_compare(char *env, char c, char *cmp);
int     ft_unsetenv(abs_struct *base);
int     ft_help(abs_struct *base);
int     vertical_line(abs_struct *base); 
void    handle_sigint(int sig);
#endif

