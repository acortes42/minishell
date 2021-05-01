/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_absolute_shell_command.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:58:39 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/01 16:58:40 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_absolute_shell_command(t_abs_struct *base,
	char *cmd, t_process *p)
{
	execve(cmd, p->argv, base->env);
	if (errno == EACCES)
		p->status = 126;
	p->completed = 1;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
