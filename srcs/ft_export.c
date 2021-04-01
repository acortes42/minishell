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

int	ft_export(t_abs_struct *base, t_process *p)
{
	if (!p->argv[1])
		return (ft_print_declares(base));
	else
		return (ft_setenv(base, p));
}
