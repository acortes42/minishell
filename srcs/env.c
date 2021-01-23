/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:16 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:04:18 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_copy_env(abs_struct *base, char **envp)
{
    int x;

    x = 0;
    base->lines_envp = 0;

    while(envp[base->lines_envp])
        base->lines_envp++;
    base->env = malloc(sizeof(char*) * (base->lines_envp - 1));
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
    {
        ft_putstr(base->env[x++]);
        ft_putstr("\n");
        base->error = 0;
    }
    return (1);
}

int ft_unsetenv(abs_struct *base)
{
    int     x;
    int     y;
    char    **aux;

    if(!base->parseString[1] || base->parseString[2])
    {
        ft_putstr("\e[0mError con los argumentos\n");
        return (-1);
    }
    x = 0;
    y = 0;
    aux = malloc(sizeof(char*) * (base->lines_envp));
    while (x < base->lines_envp)
    {
        aux[x] = ft_strdup(base->env[x]);
        x++;
    }
    base->env = malloc(sizeof(char*) * (base->lines_envp - 1));
    x = 0;
    while (x < base->lines_envp)
    {
        if (ft_find_and_compare(aux[x], '=', base->parseString[1]) != 1)
        {
            base->env[y] = ft_strdup(aux[x]);
            y++;
        }
        x++;
    }
    if (x > y && base->lines_envp > 0)
    {
        base->lines_envp--;
        base->error = 0;
    }
    else
    {
        ft_putstr("\e[0mNo se encontro la variable de entorno descrita\n");
        base->error  = 1;
    }
    free(aux);
    return (1);
}