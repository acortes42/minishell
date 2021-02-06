#include "minishell.h"

void    ft_wait_for_job (t_job *j)
{
  int status;
  pid_t pid;

  do
    pid = waitpid (-2, &status, 2); // untraced
  while (!ft_mark_process_status (j, pid, status)
         && !ft_job_is_stopped (j)
         && !ft_job_is_completed (j));
}