/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:27 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 17:10:11 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	echo(t_abs_struct *base, t_process *p)
{
	int		i;
	int		flag;

	i = 1;
	flag = 0;
	if (!p->argv[i])
		return (1);
	flag = 1;
	if (ft_strcmp(p->argv[i], "-n") == 0)
		flag = 0;
	if (flag == 0)
		i++;
	if (!p->argv[i])
		return (1);
	while (p->argv[i])
	{
		ft_putstr(p->argv[i]);
		i++;
		if (p->argv[i])
			ft_putstr(" ");
	}
	if (flag == 1)
		ft_putstr("\n");
	base->error = 0;
	return (1);
}
