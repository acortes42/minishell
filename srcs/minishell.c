#include "../minishell.h"

char *addChar(char *s1, char c)
{
    char    *str;
    int     total;
    int     n;

    n = 0;
    total = ft_strlen(s1) + 1;
    str = malloc(sizeof(char) * total);
    while (*s1)
		str[n++] = *s1++;
    str[n++] = c;
    str[n] = '\0';
    return (str);
}

// Mejorar ese horror de algoritmo que esta abajo. Da muchos errores.

int obtain_full_line(abs_struct *base)
{
    char        c;
    int         fd;

    base->string = ft_strdup("");
    fd = open("history.txt", O_RDWR | O_APPEND);
    while (read(0, &c, sizeof(char)) > 0)
    {
        write(fd, &c, 1);
        if (c == '\n')
            break;
        if (c != '\"' && c != '\'')
            base->string = addChar(base->string, c);
    }
    close(fd);
    base->parseString = ft_split(base->string, ' ');
    return (0);
}

void clearScreen()
{
    ft_putstr("\033[2J\033[1;1H");
    ft_putstr("             |||------------------------------||| \n");
    ft_putstr("             |||------------------------------||| \n");
    ft_putstr("             |||------------------------------||| \n");
    ft_putstr("             |||           MINISHELL          ||| \n");
    ft_putstr("             |||------------------------------||| \n\n\n");
}

int execute (abs_struct *base)
{   
    pid_t   pid;
    int     num_arguments;

    //manejar el ctrl+c para los bonus, cerrando todos los subprocesos de minishell
    //signal(SIGINT, handle_sigint);
    base->valid_str = ft_split("exit echo pwd cd history help env setenv unsetenv clear |", ' ');
    pid = fork();
    num_arguments = 0;
    while (base->parseString[num_arguments])
        num_arguments++;
    if (pid > 0)
        wait(&pid);
    else if (pid == 0)
    {
        while (base->actual_argument <= num_arguments)
        {
            if (ft_strcmp(base->string, base->valid_str[0]) == 0 ) 
                kill(pid, SIGKILL);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[1]) == 0)
                echo(base);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[2]) == 0)
                ft_pwd();
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[3]) == 0)
                cd(base);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[4]) == 0)
                ft_history();
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[5]) == 0)
                ft_help(base);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[6]) == 0)
                ft_env(base);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[7]) == 0)
                ft_setenv(base);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[8]) == 0)
                ft_unsetenv(base);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[9]) == 0)
                clearScreen();
           /* else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[10]) == 0)
                ft_export(base);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[11]) == 0 && base->actual_argument != 0)
                vertical_line(base);*/
            else
                ft_putstr("Error en los argumentos\n");
            base->actual_argument++;
        }
    }
    else
        ft_putstr(" Error en la creacion de subproceso\n");
    return (1);
}


int main(int argc, char **argv, char **envp)
{
    int         exceptionNum;
    abs_struct  *base;

    exceptionNum = 1;
    clearScreen();
    if (!(base = malloc(sizeof(abs_struct) * 1)))
	  	return (-1);
    ft_copy_env(base, envp);
    base->actual_argument = 0;
    base->flag = 0;
    while (exceptionNum == 1)
    {
        ft_putstr("--->");
        obtain_full_line(base);
        execute(base);         
    }
    (void)argc;
    (void)argv;
    return (0);
}