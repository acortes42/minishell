#include "minishell.h"

static void		ft_setup_pipes(abs_struct *base, t_job *j, t_process *p, t_files_fd *fds)
{
	if (p->next)
	{
		/* Set up pipes */
		if (pipe(fds->pipes) < 0)
		{
			ft_putstr_fd(strerror(errno), fds->errfile); // pipe
			ft_exit_minishell(base, 1);
		}
		fds->outfile = fds->pipes[1];
	}
	else
		fds->outfile = j->stdout;
	fds->errfile = j->stderr;
}

static void		ft_fork_child(abs_struct *base, t_process *p, t_files_fd fds)
{
	pid_t		pid;

	if (p->argv && !ft_strcmp(*p->argv, "exit"))
		ft_exit_minishell(base, 0);
	/* Fork the child processes.  */
	pid = fork ();
	//pid = 0;
	if (pid == 0)
		/* This is the child process.  */
		ft_launch_process(base, p, fds);
	else if (pid < 0)
	{
		ft_putstr_fd(strerror(errno), fds.errfile);
		ft_exit_minishell(base, 1);
	}
	else
	{
		/* This is the parent process.  */
		p->pid = pid;
		wait(&p->status);
	}
}

static void		ft_cleanup_fds(t_job *j, t_files_fd fds)
{
	/* Clean up after pipes.  */
	if (fds.infile != j->stdin)
		close(fds.infile);
	if (fds.outfile != j->stdout)
		close(fds.outfile);
}

static void		ft_launch_processes(abs_struct *base, t_job *j)
{
	t_process	*p;
	t_files_fd	fds;

	fds.infile = j->stdin;
	for (p = j->first_process; p; p = p->next)
	{
		ft_setup_pipes(base, j, p, &fds);
		ft_fork_child(base, p, fds);
		ft_cleanup_fds(j, fds);
		fds.infile = fds.pipes[0];
	}
}

void			ft_launch_job(abs_struct *base, t_job *j)
{
	ft_launch_processes(base, j);
//	ft_format_job_info(j, "launched");
//	ft_wait_for_job(j);
}
