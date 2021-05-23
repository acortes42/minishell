/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:12:45 by visv              #+#    #+#             */
/*   Updated: 2021/03/31 12:06:54 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_configure_pipes(t_process *current)
{
	if (current->next)
	{
		if (pipe(current->pipe) < 0)
		{
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
			return (0);
		}
	}
	else
	{
		current->pipe[STDIN_FILENO] = -1;
		current->pipe[STDOUT_FILENO] = -1;
	}
	return (1);
}

void	ft_close_dupped_pipes(t_process *p, int forward)
{
	while (p)
	{
		if ((forward && p->next) || !forward)
		{
			if (p->pipe[STDIN_FILENO] > -1)
				close(p->pipe[STDIN_FILENO]);
			if (p->pipe[STDOUT_FILENO] > -1)
				close(p->pipe[STDOUT_FILENO]);
			p->pipe[STDIN_FILENO] = -1;
			p->pipe[STDOUT_FILENO] = -1;
		}
		if (forward)
			p = p->next;
		else
			p = p->prev;
	}
}

void	ft_set_pipes(t_process *previous, t_process *current)
{
	extern t_abs_struct	g_base;

	if (previous && previous->pipe[STDIN_FILENO] > -1)
	{
		if (g_base.std_fds.infile < 0)
		{
			g_base.std_fds.infile = dup(STDIN_FILENO);
			dup2(previous->pipe[STDIN_FILENO], STDIN_FILENO);
		}
	}
	if (current->pipe[STDOUT_FILENO] > -1)
	{
		if (g_base.std_fds.outfile < 0)
		{
			g_base.std_fds.outfile = dup(STDOUT_FILENO);
			dup2(current->pipe[STDOUT_FILENO], STDOUT_FILENO);
		}
	}
}
