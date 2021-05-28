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
	extern t_abs_struct	g_base;
	char				*home;

	home = ft_getenv(g_base.env, "HOME");
	if (!home)
	{
		ft_putstr_fd("cd: HOME not defined\n", STDERR_FILENO);
		p->status = 1;
		g_base.last_status = p->status;
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
	extern t_abs_struct	g_base;
	char				*oldpwd;

	oldpwd = ft_getenv(g_base.env, "OLDPWD");
	if (!oldpwd)
	{
		ft_putstr_fd("cd: OLDPWD no está establecido\n", STDERR_FILENO);
		p->status = 1;
		g_base.last_status = p->status;
		return (0);
	}
	oldpwd = ft_strdup(oldpwd + 7);
	perform_chdir_and_environment_update(p, oldpwd);
	if (oldpwd)
		free(oldpwd);
	return (0);
}

static int	go_argv(t_process *p, char *path)
{
	char	*home;

	home = ft_strdup(path);
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
	extern t_abs_struct	g_base;
	int					args;
	char				*arg;

	p->status = 0;
	if (!p || !p->argv || !(*p->argv))
		ft_exit_minishell(1);
	args = ft_non_empty_args(p->argv);
	if (args >= 2)
	{
		arg = get_first_non_empty_arg(p->argv + 1);
		if (!ft_strcmp(arg, "-"))
			return (go_oldpwd(p));
		else
			return (go_argv(p, arg));
	}
	else
		return (go_home(p));
	return (0);
}
