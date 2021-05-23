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

// This function will check syntax
static int	check_command_syntax(char **argv)
{
	if (!argv || !(*argv))
		return (0);
	if (ft_strchr(*argv, '>') || ft_strchr(*argv, '<'))
	{
		ft_putstr("Syntatic error in command");
		return (0);
	}
	return (1);
}

void	ft_execute_absolute_shell_command(t_abs_struct *base,
	char *cmd, t_process *p)
{
	if (!check_command_syntax(p->argv))
		return ;
	execve(cmd, p->argv, base->env);
	if (errno == EACCES || errno == ENOEXEC)
		p->status = 126;
	else if (errno == ENOENT || errno == ENOEXEC)
		p->status = 127;
	else
		p->status = 1;
	p->completed = 1;
	base->last_status = p->status;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
