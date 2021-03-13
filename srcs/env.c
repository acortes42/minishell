/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:16 by acortes-          #+#    #+#             */
/*   Updated: 2021/02/15 17:46:29 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_copy_env(t_abs_struct *base, char **envp)
{
	if (!base)
		return (0);
	// The global environment is no the same as the process environment
	base->env = ft_array_dup(envp);
	base->lines_envp = ft_array_len(envp);
    return (1);
}

int			ft_env(t_abs_struct *base)
{
	char	**envp;

	envp = base->env;
    while(envp && *envp)
    {
        ft_putstr(*envp);
        ft_putstr("\n");
        base->error = 0;
		envp++;
    }
    return (1);
}

int			ft_unset(t_abs_struct *base, t_process *p)
{
	char	**it_new;
	size_t	i;
	size_t	j;
	char	*env;
	char	**key_value;

	if (!base->env || !p || !p->argv || !p->argv[0] || !p->argv[1])
		return (1);
	key_value = ft_split(p->argv[1], '=');
	if (!key_value || !(env = ft_getenv(base->env, key_value[0])))
	{
		ft_array_release(key_value);
		return (1);
	}
	ft_array_release(key_value);
	if (!(it_new = malloc(sizeof(char *) * base->lines_envp)))
	{
        ft_putstr("\e[0mError de memoria\n");
		return (-1);
	}
	i = 0;
	j = 0;
	while (base->env && *(base->env + i))
	{
		if (*(base->env + i) == env)
			free(env);
		else
		{
			*(it_new + j) = *(base->env + i);
			j++;
		}
		i++;
	}
	*(it_new + j) = NULL;
	free(base->env);
	base->env = it_new;
	base->lines_envp--;
	return (1);
}
