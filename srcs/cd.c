/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:24 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/16 18:31:49 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	go_home(t_process *p)
{
	char	*home;

	home = ft_getenv(g_base.env, "HOME");
	if (!home)
	{
		ft_putstr("\e[0mcd: HOME not defined\n");
		p->status = 127;
		return (1);
	}
	home = ft_strdup(home + 5);
	perform_chdir_and_environment_update(p, home);
	if (home)
		free(home);
	return (0);
}

int	go_oldpwd(t_process *p)
{
	char	*oldpwd;

	oldpwd = ft_getenv(g_base.env, "OLDPWD");
	if (!oldpwd)
	{
		ft_putstr("\e[0mcd: OLDPWD no está establecido\n");
		p->status = 127;
		return (1);
	}
	oldpwd = ft_strdup(oldpwd + 7);
	perform_chdir_and_environment_update(p, oldpwd);
	if (oldpwd)
		free(oldpwd);
	return (0);
}

static int	go_argv(t_process *p)
{
	char	*home;

	home = ft_strdup(*(p->argv + 1));
	if (!home)
		ft_exit_minishell(1);
	perform_chdir_and_environment_update(p, home);
	if (home)
		free(home);
	return (0);
}

static int	ft_non_empty_args(char **argv)
{
	int		count;
	char	*trim;

	count = 0;
	while (argv && *argv)
	{
		trim = ft_strtrim(*argv, " \t");
		if (ft_strlen(trim))
			count++;
		if (trim)
			free(trim);
		argv++;
	}
	return (count);
}

int	cd(t_process *p)
{
	int					args;

	p->status = 0;
	if (!p || !p->argv || !(*p->argv))
		ft_exit_minishell(1);
	args = ft_non_empty_args(p->argv);
	if (args > 2)
	{
		ft_putstr("\e[0mcd: demasiados argumentos\n");
		p->status = 127;
		return (1);
	}
	else if (args == 2)
	{
		if (!ft_strcmp(*(p->argv + 1), "-"))
			return (go_oldpwd(p));
		else
			return (go_argv(p));
	}
	else
		return (go_home(p));
	return (0);
}
