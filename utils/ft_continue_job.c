#include "minishell.h"

void		ft_continue_job (t_job *j, int foreground)
{
  ft_mark_job_as_running(j);
  if (foreground)
    ft_put_job_in_foreground(j, 1);
  else
    ft_put_job_in_background(j, 1);
}
