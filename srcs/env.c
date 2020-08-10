#include "../minishell.h"

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