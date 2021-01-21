#include "../minishell.h"

/*
    Parece que llega donde tiene que llegar pero falla con el chdir
*/

int cd(abs_struct *base)
{
    char    cwd[PATH_MAX];
    char    *str;

    if (base->num_args == base->actual_argument + 1)
    {
        chdir("/");
    }
    else if (base->parseString[base->actual_argument + 1][0] == '/')
    {
        if (chdir(base->parseString[1]) == 0)
        {
            ft_putstr("Busqueda de directorio correcta\n");
            chdir(base->parseString[1]);
        }
        else
            ft_putstr("Error a la asignación de directorio\n");
    }
    else if (strcmp(base->parseString[base->actual_argument + 1], "..") == 0)
    {
        chdir("..");
        ft_putstr("Tira hacia atrás\n");
    }
    else
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            str = strdup(getcwd(cwd, sizeof(cwd)));
            str = ft_strjoin(str, "/");
            str = ft_strjoin(str, base->parseString[base->actual_argument + 1]);
            if (chdir(str) == 0)
                ft_putstr("Directorio valido\n");
            else
                ft_putstr("Fallo al acceder al directorio\n");
        }
        else
            ft_putstr("Directorio no valido\n");
    }
    return (1);
}