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

void	perform_chdir_and_environment_update(t_abs_struct *base, char *home)
{
	char	*pwd;
	char	*old_pwd;

	pwd = 0;
	old_pwd = getcwd(0, 0);
	if (chdir(home))
	{
		print_file_doesnt_exist(base->parse_string[base->a + 1]);
		base->error = 1;
	}
	else
	{
		base->error = 0;
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

int	cd(t_abs_struct *base)
{
	char		*home;

	base->num_args = ft_count_until_separator(base->parse_string, base->a);
	base->error = !cd_valid_number_of_arguments(base->num_args);
	if (base->error)
		ft_putstr("\e[0mcd: Too many arguments\n");
	else if (base->num_args > 1 && !ft_isempty(base->parse_string[base->a + 1]))
		home = ft_get_absolute_path(base, base->parse_string[base->a + 1]);
	else
	{
		home = ft_getenv(base->env, "HOME");
		if (!(check_if_home(home, 1)))
			home = ft_get_absolute_path(base, home + 5);
		else
			ft_putstr("\e[0mcd: HOME not defined\n");
	}
	if (!base->error)
	{
		perform_chdir_and_environment_update(base, home);
		if (home)
			free(home);
	}
	return (!base->error);
}
