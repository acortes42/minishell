#include "../minishell.h"

int cd(abs_struct *base)
{
    char    cwd[PATH_MAX];
    char    *str;

    ft_printf("%s\n", base->parseString[1]);
    if (base->parseString[1][0] == '/')
    {
        if (chdir(base->parseString[1]) == 0)
        {
            ft_printf("Directorio valido\n");
            chdir(base->parseString[1]);
        }
        else
            ft_printf("Error a la asignacción de directorio\n");
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
                ft_printf("Directorio valido\n");
            else
                ft_printf("Fallo al acceder al directorio\n");
        }
        else
            ft_printf("Directorio no valido\n");
    }
    return (1);
}