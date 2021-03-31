/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:17 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:18:18 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_fork_child(t_abs_struct *base, t_process *previous,
	t_process *current)
{
	pid_t		pid;

	pid = fork();
	if (pid == 0)
	{
		if (signal(SIGINT, forked_process_signal_handler) == SIG_ERR)
			ft_exit_minishell(base, errno);
		ft_set_pipes(previous, current);
		ft_launch_process(base, current);
		exit(current->status);
	}
	else if (pid < 0)
		ft_exit_minishell(base, 1);
	else
	{
		current->pid = pid;
		wait(&current->status);
		current->status /= 256;
	}
}

void			ft_launch_job(t_abs_struct *base, t_job *j)
{
	t_process	*current;
	t_process	*previous;

	dup_std_fds(&j->std_fds);
	previous = 0;
	current = j->first_process;
	while (current)
	{
		ft_expand_process_cmd(base, current);
		ft_configure_pipes(base, current);
		if (!ft_execute_builtin(base, previous, current))
			ft_fork_child(base, previous, current);
		else
		{
			current->completed = 1;
			current->status = 0;
		}
		base->last_executed_process = current;
		ft_close_pipes(j->std_fds, previous, current);
		previous = current;
		current = current->next;
	}
	restore_std_fds(&j->std_fds);
}
