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

int	value_to_aux(int x)
{
	if (x > 2)
		return (0);
	return (1);
}

void	ft_aux_function(t_abs_struct *base, char *home)
{
	char	*pwd;
	char	*old_pwd;

	base->error = chdir(home);
	if (base->error)
		print_file_doesnt_exist(home);
	else
	{
		pwd = ft_getenv(base->env, "PWD");
		if (!pwd)
			ft_array_add(&base->env, &base->lines_envp,
				ft_strjoin("PWD=", pwd));
		else
			ft_array_update(&base->env, &base->lines_envp, "PWD", pwd);
		old_pwd = ft_getenv(base->env, "OLDPWD");
		if (!old_pwd)
			ft_array_add(&base->env, &base->lines_envp,
				ft_strjoin("OLDPWD=", pwd));
		else
			ft_array_update(&base->env, &base->lines_envp, "OLDPWD", pwd);
	}
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
	int			aux_nb;

	base->num_args = ft_count_until_separator(base->parse_string, base->a);
	aux_nb = value_to_aux(base->num_args);
	base->error = !aux_nb;
	if (base->error)
		ft_putstr("\e[0mcd: Too many arguments\n");
	else if (base->num_args > 1 && !ft_isempty(base->parse_string[base->a + 1]))
		home = ft_get_absolute_path(base, base->parse_string[base->a + 1]);
	else
	{
		home = ft_getenv(base->env, "HOME");
		aux_nb = check_if_home(home, aux_nb);
		if (!(aux_nb))
			home = ft_get_absolute_path(base, home + 5);
		else
			ft_putstr("\e[0mcd: HOME not defined\n");
	}
	if (!base->error)
	{
		ft_aux_function(base, home);
		free(home);
	}
	return (!base->error);
}
