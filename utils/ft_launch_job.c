/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_job.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:17 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 14:19:50 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//
// Why signal hanlder is stablished before fork? (source: man 7 signal)
// Forked process receives a copy of it's parents signals.
// And execve executions will reset signal to it's defaults, so if we set
// signals at forked child, they will be reset to parent signals in
// execve
//
static void	ft_fork_child(t_abs_struct *base, t_process *previous,
	t_process *current)
{
	pid_t		pid;

	signal(SIGINT, forked_process_signal_handler);
	signal(SIGQUIT, forked_process_signal_handler);
	pid = fork();
	if (pid == 0)
	{
		set_redirections(base, current);
		ft_set_pipes(previous, current);
		ft_launch_process(base, current);
		exit(current->status);
	}
	else if (pid < 0)
		ft_exit_minishell(1);
	else
	{
		current->pid = pid;
		wait(&current->status);
		current->status /= 256;
		base->error = current->status;
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
	}
}

void	ft_launch_job(t_abs_struct *base, t_job *j)
{
	t_process	*current;
	t_process	*previous;

	previous = 0;
	current = j->first_process;
	while (current)
	{
		ft_expand_process_cmd(base, current);
		ft_configure_pipes(current);
		if (!ft_execute_builtin(base, previous, current))
			ft_fork_child(base, previous, current);
		else
			current->completed = 1;
		base->error = current->status;
		ft_close_pipes(previous, current);
		previous = current;
		current = current->next;
	}
}
