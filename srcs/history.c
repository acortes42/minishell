#include "../minishell.h"

int ft_history(abs_struct *base)
{
    int     fd;
    int     num;
    char    **line;

    num = 1;
    line = (char**)malloc(sizeof((char**)line) * 1);
    fd = open("history.txt", O_RDWR);
    while(get_next_line(fd, line) > 0)
        ft_printf("  %d - %s\n", num++, *line);
    close(fd);
    return (1);
}