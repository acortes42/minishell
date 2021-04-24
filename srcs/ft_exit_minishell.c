/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:54:06 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 17:06:35 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_minishell(t_abs_struct *base, int exit_code)
{
	ft_setlflag(STDIN_FILENO, 1, ICANON|ECHO);
	if (exit_code && errno != 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	ft_release_base(base);
	exit(exit_code);
}
