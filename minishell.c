#include "minishell.h"

int obtain_full_line(int fd, abs_struct *base)
{
    char        str[1];

    str[strlen(str)] = '\0';
    base->string = ft_strdup("");
    fd = open("history.txt", O_RDWR | O_APPEND);
    while (read(0, str, sizeof(str)) > 0)
    {
        write(fd, str, 1);
        if (str[0] == '\n')
            break;
        base->string = ft_strjoin(base->string, str);
    }
    base->parseString = ft_split(base->string, ' ');
    return (0);
}


int execute (abs_struct *base)
{   
    pid_t   pid;

    base->valid_str = ft_split("echo exit", ' ');
    pid = fork();
    if (pid > 0)
        wait(&pid);
    else if (pid == 0)
    {
        if (strcmp(base->parseString[0], base->valid_str[0]) == 0)
            echo(base);
        else if (strcmp(base->string, base->valid_str[1]) == 0)
            kill(pid, SIGKILL);
        else
            ft_printf("Error en los argumentos\n");
    }
    else
        ft_printf(" Error en la creacion de subproceso\n");
    return (1);
}

int main(int argc, char **argv)
{
    int         fd;
    int         exceptionNum;
    abs_struct  *base;

    ft_printf("             |||           MINISHELL          ||| \n");
    ft_printf("             |||------------------------------||| \n\n\n");

    exceptionNum = 1;
    if (!(base = (abs_struct*)calloc(1, sizeof(abs_struct))))
	  	return (-1);
    while (exceptionNum == 1)
    {
        ft_printf("--->");
        obtain_full_line(fd, base);
        execute(base);
    }
    (void)argc;
    (void)argv;
    return (0);
}