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


typedef struct      abs_struct
{
    char    *env;
    char    *string;
    char    **parseString;
    char    **valid_str;
    int     exceptionNum;
    int     num_args;

}                   abs_struct;    

char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
char	*ft_strchr(char *str, int c);
char	*ft_strcdup(const char *s1, int c);
int		get_next_line(int fd, char **line);
int     ft_printf(const char *arr, ...);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
int     cd(abs_struct *base);
int     echo(abs_struct *base);
int     ft_history(abs_struct *base);
int     ft_pwd(abs_struct *base);
void    handle_sigint(int sig);
#endif

