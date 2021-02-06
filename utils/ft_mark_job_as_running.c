#include "minishell.h"

void			ft_mark_job_as_running (t_job *j)
{
	t_process	*p;

	if (!j)
		return ;
	for (p = j->first_process; p; p = p->next)
		p->stopped = 0;
  	j->notified = 0;
}


