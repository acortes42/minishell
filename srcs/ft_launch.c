/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 13:56:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 15:32:44 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_launch(abs_struct *base)
{
	char**	argv = {NULL};
  	char**	envp = {NULL};

	if (execve(base->parseString[base->actual_argument], argv, envp) == -1)
	{
		ft_putstr("\e[0mFallo en la ejecución\n");
		base->error  = 1;
	}
	else
		base->error  = 0;
	return (1);
}