#include "minishell.h"

/* Store the status of the process pid that was returned by waitpid.
   Return 0 if all went well, nonzero otherwise.  */
int				ft_mark_process_status(t_job *first_job,  pid_t pid, int status)
{
	char		*str;
	t_job		*j;
	t_process	*p;

	if (pid > 0)
	{
		/* Update the record for the process.  */
		for (j = first_job; j; j = j->next)
			for (p = j->first_process; p; p = p->next)
				if (p->pid == pid)
				{
					p->status = status;
					if (WIFSTOPPED (status))
						p->stopped = 1;
					else
					{
						p->completed = 1;
						if (WIFSIGNALED (status))
						{
							str = ft_itoa(pid);
							ft_putstr_fd(str, j->stderr);
							if (str)
								free(str);
							ft_putstr_fd(": Terminated by signal ", j->stderr);
							ft_putstr_fd(WTERMSIG(p->status) ? "1" : "0", j->stderr);
							ft_putstr_fd("\n", j->stderr);
						}
					}
					return (0);
				}
		ft_putstr_fd("No child process ", j->stderr);
		str = ft_itoa(WTERMSIG(pid));
		ft_putstr_fd(str, j->stderr);
		if (str)
			free(str);
		ft_putstr_fd("\n", j->stderr);
		return (-1);
	}
	else if (pid == 0 || errno == ECHILD)
		/* No processes ready to report.  */
		return -1;
	else
	{
		/* Other weird errors.  */
		perror ("waitpid");
		return -1;
	}
}

void			ft_update_status (abs_struct *base)
{
  int			status;
  pid_t			pid;

  do
    pid = waitpid (-2, &status, WUNTRACED|WNOHANG);
  while (!ft_mark_process_status(base->first_job, pid, status));
}