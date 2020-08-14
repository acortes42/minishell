#include "../minishell.h"

int obtain_full_line(abs_struct *base)
{
    char        str[1];
    int         fd;

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
    close(fd);
    base->parseString = ft_split(base->string, ' ');
    return (0);
}

void clearScreen()
{

    ft_printf("%s", "\033[?1049h\033[H");
    ft_printf("             |||           MINISHELL          ||| \n");
    ft_printf("             |||------------------------------||| \n\n\n");
}

int execute (abs_struct *base)
{   
    pid_t   pid;

    //manejar el ctrl+c para los bonus, cerrando todos los subprocesos de minishell
    //signal(SIGINT, handle_sigint);
    base->valid_str = ft_split("echo exit pwd cd history help env setenv unsetenv clear", ' ');
    pid = fork();
    if (pid > 0)
        wait(&pid);
    else if (pid == 0)
    {
        if (strcmp(base->parseString[0], base->valid_str[0]) == 0)
            echo(base);
        else if (strcmp(base->string, base->valid_str[1]) == 0 ) 
            kill(pid, SIGKILL);
        else if (strcmp(base->string, base->valid_str[2]) == 0)
            ft_pwd();
        else if (strcmp(base->parseString[0], base->valid_str[3]) == 0)
            cd(base);
        else if (strcmp(base->parseString[0], base->valid_str[4]) == 0)
            ft_history();
        else if (strcmp(base->parseString[0], base->valid_str[5]) == 0)
            ft_help(base);
        else if (strcmp(base->parseString[0], base->valid_str[6]) == 0)
            ft_env(base);
        else if (strcmp(base->parseString[0], base->valid_str[7]) == 0)
            ft_setenv(base);
        else if (strcmp(base->parseString[0], base->valid_str[8]) == 0)
            ft_unsetenv(base);
        else if (strcmp(base->parseString[0], base->valid_str[9]) == 0)
            clearScreen();
        else
            ft_printf("Error en los argumentos\n");
    }
    else
        ft_printf(" Error en la creacion de subproceso\n");
    return (1);
}


int main(int argc, char **argv, char **envp)
{
    int         exceptionNum;
    abs_struct  *base;

    ft_printf("             |||           MINISHELL          ||| \n");
    ft_printf("             |||------------------------------||| \n\n\n");

    exceptionNum = 1;
    if (!(base = malloc(sizeof(abs_struct) * 1)))
	  	return (-1);
    ft_copy_env(base, envp);
    while (exceptionNum == 1)
    {
        ft_printf("--->");
        obtain_full_line(base);
        execute(base);         
    }
    (void)argc;
    (void)argv;
    return (0);
}