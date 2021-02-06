#include "minishell.h"

void
ft_do_job_notification (t_job *first_job)
{
  t_job *j, *jlast, *jnext;

  /* Update status information for child processes.  */
  //update_status ();

  jlast = NULL;
  for (j = first_job; j; j = jnext)
    {
      jnext = j->next;

      /* If all processes have completed, tell the user the job has
         completed and delete it from the list of active jobs.  */
      if (ft_job_is_completed (j)) {
        ft_format_job_info (j, "completed");
        if (jlast)
          jlast->next = jnext;
        else
          first_job = jnext;
        ft_free_job (j);
      }

      /* Notify the user about stopped jobs,
         marking them so that we won’t do this more than once.  */
      else if (ft_job_is_stopped (j) && !j->notified) {
        ft_format_job_info (j, "stopped");
        j->notified = 1;
        jlast = j;
      }

      /* Don’t say anything about jobs that are still running.  */
      else
        jlast = j;
    }
}