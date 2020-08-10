#include "../minishell.h"


// Problema al solo aceptar dos introducciones con setenv

int ft_find_and_compare(char *env, char c, char *cmp)
{
    char    *aux;
    int     x;
    int     y;

    x = 0;
    while(env[x] != c)
        x++;
    aux = malloc(sizeof(char) * x);
    strncpy(aux, env, x);
    if (strcmp(aux, cmp) == 0)
        return (1);
  //  ft_printf("Valor aux: %s||||\n", aux);
  //  ft_printf("Valor cmp: %s||||\n", cmp);
    free(aux);
    return (0);
}

int ft_seach(abs_struct *base)
{
    int x;

    x = 0;
    while (base->env[x])
    {
        if (ft_find_and_compare(base->env[x], '=', base->parseString[1]) == 1)
        {
            ft_printf("Esto es antes: %s\n", base->env[x]);
            free(base->env[x]);
            base->env[x] = ft_strdup(base->parseString[1]);
            base->env[x] = ft_strjoin(base->env[x], "=");
            base->env[x] = ft_strjoin(base->env[x], base->parseString[2]);
            ft_printf("Esto es despues: %s\n", base->env[x]);
            return (1);
        }
        x++;
    }
    return (0);
}

int ft_add_line(char **text)
{
    char    **aux;
    int     x;

    x = 0;
    while (text[x])
        x++;
    aux = malloc(sizeof(char*) * (x + 1));
    x = 0;
    while (text[x])
    {
        aux[x] = ft_strdup(text[x]);
        x++;
    }
    text = malloc(sizeof(aux));
    ft_printf("%d", x);
    x = 0;
    while (aux[x])
    {
        text[x] = ft_strdup(aux[x]);
        x++;
    }
    free(aux);
    return (x);
}

int ft_setenv(abs_struct *base)
{
    if (base->parseString[1] && base->parseString[2] && !base->parseString[3])
    {
        if (ft_seach(base) == 0)
        {
            static int  x;

            ft_printf("%d\n", x);
            ft_add_line(base->env);
            base->env[base->lines_envp + x] = ft_strdup(base->parseString[1]);
            base->env[base->lines_envp + x] = ft_strjoin(base->env[base->lines_envp + x], "=");
            base->env[base->lines_envp + x] = ft_strjoin(base->env[base->lines_envp + x], base->parseString[2]);
            x++;
            return (1);
        }
    }
    ft_printf("Error al añadir env");
    return (0);
}