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

int ft_add_line(char **text, abs_struct *base)
{
    char    **aux;
    int     x;

    x = 0;
    while (text[x])
        x++;
    ft_printf("text -- %s\n", text[x - 1]);
    aux = malloc(sizeof(char*) * (x + 1));
    x = 0;
    while (text[x])
    {
        aux[x] = ft_strdup(text[x]);
        x++;
    }
    ft_printf("aux antes -- %s\n", aux[x - 1]);
    aux[x] = ft_strdup(base->parseString[1]);
    aux[x] = ft_strjoin(base->env[base->lines_envp + x], "=");
    aux[x] = ft_strjoin(base->env[base->lines_envp + x], base->parseString[2]);
    ft_printf("aux -- %s\n", aux[x]);
    text = malloc(sizeof(char*) * (x + 1) );
    x = 0;
    while (aux[x])
    {
        text[x] = ft_strdup(aux[x]);
        x++;
    }
    ft_printf("%s\n", aux[x]);
    free(aux);
    return (x);
}

int ft_setenv(abs_struct *base)
{
    if (base->parseString[1] && base->parseString[2] && !base->parseString[3])
    {
        if (ft_seach(base) == 0)
        {
            ft_add_line(base->env, base);
            return (1);
        }
    }
    ft_printf("Error al añadir env");
    return (0);
}