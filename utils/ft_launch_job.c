#include "minishell.h"

static void		ft_setup_pipes(abs_struct *base, t_job *j, t_process *p, t_files_fd *fds)
{
	if (p->next)
	{
		/* Set up pipes */
		if (pipe(fds->pipes) < 0)
			ft_exit_minishell(base, 1);
		fds->outfile = fds->pipes[1];
	}
	else
		fds->outfile = j->std_fds.outfile;
	fds->errfile = j->std_fds.errfile;
}

static void		ft_fork_child(abs_struct *base, t_process *p, t_files_fd fds)
{
	pid_t		pid;

	if (signal(SIGINT, forked_process_signal_handler) == SIG_ERR)
		ft_exit_minishell(base, errno);
	pid = fork();
	//pid = 0;
	if (pid == 0)
	{
		ft_launch_process(base, p, fds);
		exit(p->status);
	}
	else if (pid < 0)
		ft_exit_minishell(base, 1);
	else
	{
		p->pid = pid;
		wait(&p->status);
		p->status /= 256;
	}
}

static void		ft_cleanup_fds(t_files_fd fds)
{
	if (fds.infile > -1 && fds.infile != STDIN_FILENO)
	{
		close(fds.infile);
	}
	if (fds.outfile > -1 && fds.outfile != STDOUT_FILENO)
	{
		ft_putstr("Closing outfile:");
		char *out = ft_itoa(fds.outfile);
		ft_putstr(out);
		ft_putstr("\n");
		free(out);
		close(fds.outfile);
	}
}

void			ft_launch_job(abs_struct *base, t_job *j)
{
	t_process	*p;
	t_files_fd	fds;
	t_files_fd	std_fds;

	dup_std_fds(&std_fds);
	fds.infile = j->std_fds.infile;
	for (p = j->first_process; p; p = p->next)
	{
		if (ft_execute_builtin(base, p))
		{
			p->completed = 1;
			p->status = 0;
			continue ;
		}
		ft_setup_pipes(base, j, p, &fds);
		ft_fork_child(base, p, fds);
		ft_cleanup_fds(fds);
		fds.infile = fds.pipes[0];
	}
	restore_std_fds(std_fds);
}
