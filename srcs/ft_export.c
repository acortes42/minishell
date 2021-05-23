/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:55:18 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 17:06:21 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_print_declare(char *env)
{
	int		space;
	char	*value;

	value = ft_strchr(env, '=');
	if (!(value))
		return (0);
	space = ft_isspace(*(value + 1));
	ft_putstr("declare -x ");
	ft_putnstr(env, (value - env + 1));
	if (space)
		ft_putstr("\"");
	ft_putstr((env + (value - env + 1)));
	if (space)
		ft_putstr("\"");
	ft_putstr("\n");
	return (1);
}

static int	ft_print_declares(t_abs_struct *base)
{
	char	**it;

	it = base->env;
	while (it && *it)
	{
		ft_print_declare(*it);
		it++;
	}
	return (1);
}

int	extract_key_value(char *args, char	***key_value, int *value_to_add)
{
	*key_value = ft_split_key_value_pair(args, '=');
	if (!(*key_value))
	{
		*value_to_add = 0;
		return (is_env_valid_argument(args));
	}
	else if (***key_value == '$' && *((**key_value) + 1))
	{
		ft_array_release(*key_value);
		*key_value = 0;
		*value_to_add = 0;
		return (1);
	}
	else if (!is_env_valid_argument(**key_value))
	{
		ft_array_release(*key_value);
		*key_value = 0;
		*value_to_add = 0;
		return (1);
	}
	*value_to_add = 1;
	return (0);
}

void	ft_export(t_abs_struct *base, t_process *p)
{
	char	*first_non_empty;
	char	**args;

	p->status = 0;
	first_non_empty = get_first_non_empty_arg(p->argv + 1);
	if (!first_non_empty)
		ft_print_declares(base);
	else
	{
		args = p->argv + 1;
		while (args && *args)
		{
			if (!ft_setenv(base, *args))
			{
				p->status = 1;
				base->last_status = p->status;
				ft_putstr_fd("export: `", STDERR_FILENO);
				ft_putstr_fd(*args, STDERR_FILENO);
				ft_putstr_fd("': Invalid identifier\n", STDERR_FILENO);
			}
			args++;
		}
	}
}
