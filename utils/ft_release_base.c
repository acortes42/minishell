#include "minishell.h"

void		ft_release_base(abs_struct *base)
{
	if (!base)
		return ;
	ft_array_release(base->env);
	// Este se libera al liberar el job
	base->parseString = 0;
	ft_release_jobs(base->first_job);
	base->first_job = 0;
	return ;
}

