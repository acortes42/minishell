#include "../minishell.h"


// Problema al solo aceptar dos introducciones con setenv

int ft_find_and_compare(char *env, char c, char *cmp)
{
    char    *aux;
    int     x;

    x = 0;
    while(env[x] != c)
        x++;
    aux = malloc(sizeof(char) * x);
    strncpy(aux, env, x);
    if (ft_strcmp(aux, cmp) == 0)
    {
        free(aux);
        return (1);
    }
    free(aux);
    return (0);
}

int ft_seach(abs_struct *base)
{
    int x;

    x = 0;
    while (x < base->lines_envp)
    {
        if (ft_find_and_compare(base->env[x], '=', base->parseString[1]) == 1)
        {
            free(base->env[x]);
            base->env[x] = ft_strdup(base->parseString[1]);
            base->env[x] = ft_strjoin(base->env[x], "=");
            base->env[x] = ft_strjoin(base->env[x], base->parseString[2]);
            return (1);
        }
        x++;
    }
    return (0);
}

/*Existe un problema al crear al crear más memoria y copiar lo necesario*/

int ft_add_line(abs_struct *base)
{
    char    **aux;
    int     x;

    x = 0;
    aux = malloc(sizeof(char*) * (base->lines_envp));
    while (x < base->lines_envp)
    {
        aux[x] = ft_strdup(base->env[x]);
        x++;
    }
    aux[x] = ft_strdup(base->parseString[1]);
    aux[x] = ft_strjoin(aux[x], "=");
    aux[x] = ft_strjoin(aux[x], base->parseString[2]);
    base->env = malloc(sizeof(char*) * (base->lines_envp));
    x = 0;
    while (x <= base->lines_envp)
    {
        base->env[x] = ft_strdup(aux[x]);
        x++;
    }
    base->lines_envp++;
    free(aux);
    return (1);
}

int ft_setenv(abs_struct *base)
{

    if (base->parseString[1] && base->parseString[2] && !base->parseString[3])
    {
        if (ft_seach(base) == 0)
            ft_add_line(base);
        return (1);
    }
    ft_putstr("Error en los argumentos\n");
    base->error  = 0;
    return (0);
}