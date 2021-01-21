#include "../minishell.h"

int obtain_full_line(abs_struct *base)
{
    char        c;
    int         fd;
    int         i;

    fd = open("history.txt", O_RDWR | O_APPEND);
    i = 0;
    while (read(0, &c, sizeof(char)) > 0)
    {
        write(fd, &c, 1);
        if (c == '\n')
            break;
        if (c != '\"' && c != '\'')
        {
            base->string[i] = c;
            i++;
        }
    }
    base->string[i] = '\0';
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

    base->valid_str = ft_split("exit echo pwd cd history help env setenv unsetenv clear |", ' ');
    pid = fork();

    if (pid > 0)
        wait(&pid);
    else if (pid == 0)
    {
        base->num_args = 0;
        while (base->parseString[base->num_args])
            base->num_args++;
        base->actual_argument = 0;
        while (base->actual_argument <= base->num_args)
        {
            if (ft_strcmp(base->string, base->valid_str[0]) == 0 ) 
                kill(pid, SIGKILL);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[1]) == 0)
                echo(base);
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[2]) == 0)
                ft_pwd();
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[3]) == 0)
            {    
                 cd(base);
                 base->actual_argument += 1;
            }
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
                ft_export(base); */
            else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[11]) == 0 && base->actual_argument != 0)
                vertical_line(base);
            else
                ft_putstr("Error en los argumentos\n");
            base->actual_argument++;

            // manejo de ; |
            if (ft_strcmp(base->parseString[base->actual_argument],  ";") == 0)
                base->actual_argument++;
            else if (ft_strcmp(base->parseString[base->actual_argument],  "|") == 0)
            {
                // pensar en equipo como gestionar esto
                base->actual_argument++;
            }
            else
                break;
            
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

    signal(SIGINT, handle_sigint);
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