#include "minishell.h"

static void		ft_create_pipes(abs_struct *base, t_process *current)
{
	if (current->next)
	{
		if (pipe(current->pipe) < 0)
			ft_exit_minishell(base, errno);
	}
	else
	{
		current->pipe[STDIN_FILENO] = -1;
		current->pipe[STDOUT_FILENO] = -1;
	}
}

static void		ft_close_pipes(t_process *previous, t_process *current)
{
	if (previous)
	{
		if (previous->pipe[STDIN_FILENO] > -1)
			close(previous->pipe[STDIN_FILENO]);
	}
	if (current->pipe[STDOUT_FILENO] > -1)
		close(current->pipe[STDOUT_FILENO]);
}

static void		ft_fork_child(abs_struct *base, t_process *previous,
	t_process *current)
{
	pid_t		pid;

	if (signal(SIGINT, forked_process_signal_handler) == SIG_ERR)
		ft_exit_minishell(base, errno);
	pid = fork();
	//pid = 0;
	if (pid == 0)
	{
		ft_launch_process(base, previous, current);
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

void			ft_launch_job(abs_struct *base, t_job *j)
{
	t_process	*current;
	t_process	*previous;

	dup_std_fds(&j->std_fds);
	previous = 0;
	for (current = j->first_process; current; current = current->next)
	{
		ft_expand_process_cmd(base, current);
		if (ft_execute_builtin(base, current))
		{
			current->completed = 1;
			current->status = 0;
			continue ;
		}
		ft_create_pipes(base, current);
		ft_fork_child(base, previous, current);
		ft_close_pipes(previous, current);
		previous = current;
	}
	restore_std_fds(&j->std_fds);
}
