#include "minishell.h"

void            ft_launch_process(abs_struct *base, t_process *p, t_files_fd files_fd)
{
	/* Set the handling for job control signals back to the default.  */
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	/* Set the standard input/output channels of the new process.  */
	if (files_fd.infile != STDIN_FILENO)
	{
		dup2(files_fd.infile, STDIN_FILENO);
		close(files_fd.infile);
	}
	if (files_fd.outfile != STDOUT_FILENO)
	{
		dup2(files_fd.outfile, STDOUT_FILENO);
		close(files_fd.outfile);
	}
	if (files_fd.errfile != STDERR_FILENO)
	{
		dup2(files_fd.errfile, STDERR_FILENO);
		close(files_fd.errfile);
	}
	if (ft_execute_builtin(base, p))
	{
		p->completed = 1;
		p->status = 0;
		exit(p->status);
	}
	else
	{
		if (execve(p->argv[0], p->argv, base->env) && errno == EACCES)
		{
			p->status = 126;
		}
		p->completed = 1;
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
}