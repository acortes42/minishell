/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:27 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/15 14:59:51 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_args(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		ft_putstr(argv[i]);
		i++;
		if (argv[i])
			ft_putstr(" ");
	}
}

int	ft_echo(t_abs_struct *base, t_process *p)
{
	int		i;
	int		flag;

	i = 1;
	if (!p->argv[i])
	{
		ft_putstr("\n");
		return (1);
	}
	flag = 1;
	if (ft_strcmp(p->argv[i], "-n"))
		flag = 0;
	if (flag)
		i++;
	if (!p->argv[i])
	{
		if (!flag)
			ft_putstr("\n");
		return (1);
	}
	echo_args(p->argv + i);
	if (!flag)
		ft_putstr("\n");
	base->error = 0;
	return (1);
}
