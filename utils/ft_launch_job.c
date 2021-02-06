#include "minishell.h"

void			ft_launch_job (abs_struct *base, t_job *j, int foreground)
{
	int			shell_is_interactive;
  t_process		*p;
  pid_t			pid;
  t_files_fd	fds;

	shell_is_interactive = 1;
  fds.infile = j->stdin;
  for (p = j->first_process; p; p = p->next)
    {
      /* Set up pipes, if necessary.  */
      if (p->next)
        {
          if (pipe (fds.pipes) < 0)
            {
              ft_putstr_fd(strerror(errno), fds.errfile); // pipe
	          ft_exit_minishell(base, 1);
            }
          fds.outfile = fds.pipes[1];
        }
      else
        fds.outfile = j->stdout;
		fds.errfile = j->stderr;
      /* Fork the child processes.  */
      pid = fork ();
      if (pid == 0)
        /* This is the child process.  */
        ft_launch_process (j, p, fds, foreground);
      else if (pid < 0)
        {
          ft_putstr_fd(strerror(errno), fds.errfile);
          ft_exit_minishell(base, 1);
        }
      else
        {
          /* This is the parent process.  */
          p->pid = pid;
          if (shell_is_interactive)
            {
              if (!j->pgid)
                j->pgid = pid;
            }
        }

      /* Clean up after pipes.  */
      if (fds.infile != j->stdin)
        close (fds.infile);
      if (fds.outfile != j->stdout)
        close (fds.outfile);
      fds.infile = fds.pipes[0];
    }

  ft_format_job_info (j, "launched");

  if (!shell_is_interactive)
    ft_wait_for_job (j);
  else if (foreground)
    ft_put_job_in_foreground (j, 0);
  else
    ft_put_job_in_background (j, 0);
}
