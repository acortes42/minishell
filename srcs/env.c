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

int			ft_copy_env(t_abs_struct *base, char **envp)
{
	if (!base)
		return (0);
	base->env = ft_array_dup(envp);
	base->lines_envp = ft_array_len(envp);
	return (1);
}

int			ft_env(t_abs_struct *base)
{
	char	**envp;

	envp = base->env;
	while (envp && *envp)
	{
		ft_putstr(*envp);
		ft_putstr("\n");
		base->error = 0;
		envp++;
	}
	return (1);
}

static char	*ft_get_env_to_unset(t_abs_struct *base, t_process *p)
{
	char	*env;
	char	**key_value;

	if (!base->env || !p || !p->argv || !p->argv[0] || !p->argv[1])
		return (0);
	key_value = ft_split(p->argv[1], '=');
	if (!key_value || !(env = ft_getenv(base->env, key_value[0])))
	{
		ft_array_release(key_value);
		return (0);
	}
	ft_array_release(key_value);
	return (env);
}

static char	**ft_array_dup_without(char **env, size_t len_env, char *not_dup)
{
	char	**it_new;
	size_t	i;
	size_t	j;

	if (!(it_new = malloc(sizeof(char *) * len_env)))
	{
		ft_putstr("\e[0mError de memoria\n");
		return (0);
	}
	i = 0;
	j = 0;
	while (env && *(env + i))
	{
		if (*(env + i) != not_dup)
		{
			*(it_new + j) = *(env + i);
			j++;
		}
		i++;
	}
	*(it_new + j) = NULL;
	return (it_new);
}

int			ft_unset(t_abs_struct *base, t_process *p)
{
	char	**it_new;
	char	*env;

	if (!(env = ft_get_env_to_unset(base, p)))
		return (1);
	if ((it_new = ft_array_dup_without(base->env, base->lines_envp, env)))
	{
		free(base->env);
		base->env = it_new;
		base->lines_envp--;
	}
	free(env);
	return (it_new ? 1 : 0);
}
