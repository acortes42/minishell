#include "minishell.h"

void	ft_format_job_info (t_job *j, const char *status)
{
  fprintf (stderr, "%ld (%s): %s\n", (long)j->pgid, status, j->command);
}