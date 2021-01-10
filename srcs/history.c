#include "../minishell.h"

int ft_history()
{
    int     fd;
    int     num;
    char    **line;

    num = 1;
    line = malloc(sizeof((char**)line) * 1);
    fd = open("history.txt", O_RDWR);
    while(get_next_line(fd, line) > 0)
    {
        ft_putstr("  ");
        ft_putnbr(num++);
        ft_putstr(" - ");
        ft_putstr(*line);
        ft_putstr("\n");
    }
    close(fd);
    return (1);
}