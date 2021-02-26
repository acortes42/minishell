#include "minishell.h"

static void		ft_init_current_io(abs_struct *base, t_process *current)
{
	current->std_fds.infile = STDIN_FILENO;
	current->std_fds.outfile = STDOUT_FILENO;
	current->std_fds.errfile = STDERR_FILENO;
	if (current->next)
	{
		if (pipe(current->std_fds.pipes) < 0)
			ft_exit_minishell(base, errno);
	}
	else
	{
		current->std_fds.pipes[0] = -1;
		current->std_fds.pipes[1] = -1;
	}
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
		if (ft_execute_builtin(base, current))
		{
			current->completed = 1;
			current->status = 0;
			continue ;
		}
		ft_init_current_io(base, current);
		ft_fork_child(base, previous, current);
		if (previous && previous->std_fds.pipes[1] > -1)
			close(previous->std_fds.pipes[1]);
		if (current->next && current->std_fds.pipes[0] > -1)
			close(current->std_fds.pipes[0]);
		previous = current;
	}
	restore_std_fds(&j->std_fds);
}
