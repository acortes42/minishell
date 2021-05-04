/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:16 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 17:09:20 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_copy_env(t_abs_struct *base, char **envp)
{
	if (!base)
		return (0);
	base->env = ft_array_dup(envp);
	base->lines_envp = ft_array_len(envp);
	return (1);
}

int	ft_env(t_abs_struct *base)
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
	env = ft_getenv(base->env, key_value[0]);
	if (!key_value || !(env))
	{
		ft_array_release(key_value);
		return (0);
	}
	ft_array_release(key_value);
	return (env);
}

int	ft_unset(t_abs_struct *base, t_process *p)
{
	char	**it_new;
	char	*env;

	env = ft_get_env_to_unset(base, p);
	if (!(env))
		return (1);
	it_new = ft_array_dup_without(base->env, base->lines_envp, env);
	if (it_new)
	{
		free(base->env);
		base->env = it_new;
		base->lines_envp--;
	}
	free(env);
	if (it_new)
		return (1);
	return (0);
}
