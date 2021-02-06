#include "minishell.h"

void            ft_launch_process (t_job *j, t_process *p, t_files_fd files_fd, int foreground)
{
	int			shell_is_interactive;
	pid_t		pid;

	(void)pid;
	(void)foreground;
	shell_is_interactive = 1;
  if (shell_is_interactive)
    {
      if (!j->pgid)
	  	j->pgid = p->pid;
      //if (foreground)
//        tcsetpgrp (shell_terminal, pgid);

      /* Set the handling for job control signals back to the default.  */
      signal (SIGINT, SIG_DFL);
      signal (SIGQUIT, SIG_DFL);
      signal (SIGTSTP, SIG_DFL);
      signal (SIGTTIN, SIG_DFL);
      signal (SIGTTOU, SIG_DFL);
      signal (SIGCHLD, SIG_DFL);
    }

  /* Set the standard input/output channels of the new process.  */
  if (files_fd.infile != STDIN_FILENO)
    {
      dup2 (files_fd.infile, STDIN_FILENO);
      close (files_fd.infile);
    }
  if (files_fd.outfile != STDOUT_FILENO)
    {
      dup2 (files_fd.outfile, STDOUT_FILENO);
      close (files_fd.outfile);
    }
  if (files_fd.errfile != STDERR_FILENO)
    {
      dup2 (files_fd.errfile, STDERR_FILENO);
      close (files_fd.errfile);
    }

  /* Exec the new process.  Make sure we exit.  */
  execve(p->argv[0], p->argv, p->envp);
  perror ("execve");
  exit (1);
}