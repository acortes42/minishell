#include "minishell.h"

int cd(abs_struct *base)
{
    char    **aux;
    char    *str;
    int     x;
    int     count;

    ft_printf("%s\n", base->parseString[1]);
    if (base->parseString[1][0] == '.' && base->parseString[1][1] == '/')
    {
        ft_printf("Directorio valido\n");
        chdir(base->parseString[1]) == 0;
        ft_strlcpy(base->env, base->parseString[1], ft_strlen(base->parseString[1]) + 1);
    }
    else if (strcmp(base->parseString[1], "..") == 0)
    {
        x = 0;
        count = 0;
        aux = ft_split(base->env, '/');
        str = ft_strdup("");
        while (aux[x])
            ft_printf("%s : %d\n", aux[x], x++);
        while (count < x - 1)
        {
            str = ft_strjoin(str, aux[count++]);
            str = ft_strjoin(str, "/");
        }
        ft_printf("%s", str);
        ft_strlcpy(base->env, str, ft_strlen(str));
        free(aux);
    }
    else
        ft_printf("Directorio no valido\n");
    return (1);
}