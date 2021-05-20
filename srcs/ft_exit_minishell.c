/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:54:06 by visv              #+#    #+#             */
/*   Updated: 2021/05/01 16:00:26 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_adjust_exit_value(int exit_code)
{
	int	exit;

	if (exit_code >= 0)
		exit = exit_code % 256;
	else
		exit = 256 + (exit_code % 256);
	return (exit);
}

void	ft_exit_minishell(int exit_code)
{
	extern t_abs_struct	g_base;

	ft_setlflag(STDIN_FILENO, 1, g_base.c_lflag);
	if (exit_code && errno != 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	ft_release_base(&g_base);
	exit(exit_code);
}
