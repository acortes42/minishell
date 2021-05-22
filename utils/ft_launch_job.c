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

static void	execute_child(t_abs_struct *base, t_process *current)
{
	if (current->next)
	{
		dup2(current->pipe[STDOUT_FILENO], STDOUT_FILENO);
		close(current->pipe[STDIN_FILENO]);
		close(current->pipe[STDOUT_FILENO]);
	}
	if (current->prev)
	{
		dup2(current->prev->pipe[STDIN_FILENO], STDIN_FILENO);
		close(current->prev->pipe[STDIN_FILENO]);
		close(current->prev->pipe[STDOUT_FILENO]);
		ft_close_dupped_pipes(current->prev->prev, 0);
	}
	if (ft_isbuiltin(current))
		ft_execute_builtin(base, current);
	else
		ft_launch_process(base, current);
	exit(current->status);
}

//
// Why signal hanlder is stablished before fork? (source: man 7 signal)
// Forked process receives a copy of it's parents signals.
// And execve executions will reset signal to it's defaults, so if we set
// signals at forked child, they will be reset to parent signals in
// execve
//
static void	ft_fork_child(t_abs_struct *base, t_process *current)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		ft_exit_minishell(1);
	else if (!pid)
		execute_child(base, current);
	else
	{
		current->pid = pid;
		ft_wait_for_process(current);
	}
}

static int	prepare_current_process_to_execute(t_process *current)
{
	extern t_abs_struct	g_base;

	g_base.current_process = current;
	ft_expand_process_cmd(&g_base, current);
	if (!ft_configure_pipes(current)
		|| set_redirections(&g_base, current) < 0)
	{
		current->status = 1;
		current->completed = 1;
		g_base.last_status = current->status;
		return (0);
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

void	ft_launch_job(t_abs_struct *base, t_job *j)
{
	t_process	*current;

	current = j->first_process;
	while (current)
	{
		if (prepare_current_process_to_execute(current))
		{
			if (current->next || current->prev || !ft_isbuiltin(current))
				ft_fork_child(base, current);
			else
				current->completed = ft_execute_builtin(base, current);
		}
		current = current->next;
	}
	ft_close_dupped_pipes(j->first_process, 1);
	ft_wait_for_childs(j);
}
