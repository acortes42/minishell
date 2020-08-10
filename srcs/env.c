#include "../minishell.h"

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
    return (x);
}

int ft_copy_env(abs_struct *base, char **envp)
{
    int x;

    x = 0;
    base->lines_envp = 0;

    while(envp[base->lines_envp])
        base->lines_envp++;
    ft_printf("%d\n", base->lines_envp);
    base->env = malloc(sizeof(char*) * base->lines_envp + 1);
    while(envp[x])
    {
        base->env[x] = ft_strdup(envp[x]);
        x++;
    }
    return (1);
}

int ft_env(abs_struct *base)
{
    int x;

    x = 0;
    while(base->env[x])
        ft_printf("%s\n", base->env[x++]);
    return (1);
}

//falta que las conincidencias sean sustituidas

int ft_setenv(abs_struct *base)
{
    if (base->parseString[1] && base->parseString[2] && !base->parseString[3])
    {
        static int  x;

        ft_add_line(base->env);
        base->env[base->lines_envp + x] = ft_strdup(base->parseString[1]);
        base->env[base->lines_envp + x] = ft_strjoin(base->env[base->lines_envp + x], "=");
        base->env[base->lines_envp + x] = ft_strjoin(base->env[base->lines_envp + x], base->parseString[2]);
        x++;
        return (1);
    }
    ft_printf("Error al añadir env");
    return (0);
}


// lo de bajo es nada
int ft_unsetenv(abs_struct *base)
{
    int x;

    x = 0;
    while (base->env[x])
        x++;
    base->env[x - 1] == NULL;
    return (1);
}