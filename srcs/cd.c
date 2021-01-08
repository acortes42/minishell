#include "../minishell.h"

int cd(abs_struct *base)
{
    char    cwd[PATH_MAX];
    char    *str;

    if (base->parseString[1][0] == '/')
    {
        if (chdir(base->parseString[1]) == 0)
        {
            ft_putstr("Directorio valido\n");
            chdir(base->parseString[1]);
        }
        else
            ft_putstr("Error a la asignacción de directorio\n");
    }
    else if (strcmp(base->parseString[1], "..") == 0)
    {
        chdir("..");
    }
    else
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            str = strdup(getcwd(cwd, sizeof(cwd)));
            str = ft_strjoin(str, "/");
            str = ft_strjoin(str, base->parseString[1]);
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