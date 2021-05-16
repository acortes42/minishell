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

int	cd_valid_number_of_arguments(int x)
{
	if (x > 2)
		return (0);
	return (1);
}

static void	perform_chdir_and_environment_update(t_process *p, char *home)
{
	char	*pwd;
	char	*old_pwd;
	char	*path;
	int		changed_dir;
	extern	t_abs_struct	g_base;

	pwd = 0;
	old_pwd = getcwd(0, 0);
	changed_dir = !chdir(home);
	if (!changed_dir)
	{
		path = get_first_non_empty_arg(p->argv + 1);
		print_file_doesnt_exist(path);
	}
	pwd = getcwd(0, 0);
	if (!pwd)
	{
		ft_putstr(strerror(errno));
		ft_putstr("\n");
	}
	if (!changed_dir)
	{
		p->status = 127;
		if (old_pwd)
			free(old_pwd);
		old_pwd = ft_strdup(ft_getenv(g_base.env, "PWD") + 4);
		ft_update_environment_pwds(old_pwd, home);
	}
	else
	{
		p->status = 0;
		ft_update_environment_pwds(old_pwd, pwd);
	}
	if (pwd)
		free(pwd);
	if (old_pwd)
		free(old_pwd);
}

int	check_if_home(char *home, int aux)
{
	if (home)
		return (0);
	return (aux);
}

int	cd(t_process *p)
{
	extern t_abs_struct	g_base;
	char		*home;
	int			args;

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
