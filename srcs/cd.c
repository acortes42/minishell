/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:24 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 18:00:20 by acortes-         ###   ########.fr       */
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

	pwd = 0;
	old_pwd = getcwd(0, 0);
	if (chdir(home))
	{
		print_file_doesnt_exist(get_first_non_empty_arg(p->argv + 1));
		p->status = 1;
	}
	else
	{
		p->status = 0;
		pwd = getcwd(0, 0);
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
		home = ft_get_absolute_path(&g_base, get_first_non_empty_arg(p->argv + 1));
	else
	{
		home = ft_getenv(g_base.env, "HOME");
		if (!home)
		{
			ft_putstr("\e[0mcd: HOME not defined\n");
			p->status = 1;
			return (1);
		}
		home = ft_get_absolute_path(&g_base, home + 5);
	}
	perform_chdir_and_environment_update(p, home);
	if (home)
		free(home);
	return (g_base.error);
}
