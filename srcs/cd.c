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

static char	*get_first_non_empty_arg(char **args)
{
	char	*trim;

	while (*args)
	{
		trim = ft_strtrim(*args, " \t");
		if (ft_strlen(trim))
		{
			free (trim);
			return (*args);
		}
		if (trim)
			free(trim);
		args++;
	}
	return (0);
}

static void	print_file_doesnt_exist(char *file)
{
	ft_putstr("\e[0mcd: ");
	if (file)
		ft_putstr(file);
	ft_putstr(": File or dir doesn't exist\n");
}

static void	perform_environment_update(t_env_update *info)
{
	extern t_abs_struct	g_base;

	if (!info->changed_dir)
	{
		info->p->status = 127;
		if (info->old_pwd)
			free(info->old_pwd);
		info->old_pwd = ft_strdup(ft_getenv(g_base.env, "PWD") + 4);
		ft_update_environment_pwds(info->old_pwd, info->home);
	}
	else
	{
		info->p->status = 0;
		ft_update_environment_pwds(info->old_pwd, info->pwd);
	}
	if (info->pwd)
		free(info->pwd);
	if (info->old_pwd)
		free(info->old_pwd);
}

static void	perform_chdir_and_environment_update(t_process *p, char *home)
{
	t_env_update		info;
	char				*path;

	info.pwd = 0;
	info.old_pwd = getcwd(0, 0);
	info.changed_dir = !chdir(home);
	if (!info.changed_dir)
	{
		path = get_first_non_empty_arg(p->argv + 1);
		print_file_doesnt_exist(path);
	}
	info.pwd = getcwd(0, 0);
	if (!info.pwd)
	{
		ft_putstr(strerror(errno));
		ft_putstr("\n");
	}
	info.home = home;
	info.p = p;
	perform_environment_update(&info);
}

int	cd(t_process *p)
{
	extern t_abs_struct	g_base;
	char				*home;
	int					args;

	p->status = 0;
	if (!p || !p->argv || !(*p->argv))
		ft_exit_minishell(1);
	args = ft_array_len(p->argv);
	if (args > 1)
		home = ft_strdup(*(p->argv + 1));
	else
	{
		home = ft_getenv(g_base.env, "HOME");
		if (!home)
		{
			ft_putstr("\e[0mcd: HOME not defined\n");
			p->status = 127;
			return (1);
		}
		home = ft_strdup(home + 5);
	}
	perform_chdir_and_environment_update(p, home);
	if (home)
		free(home);
	return (g_base.error);
}
