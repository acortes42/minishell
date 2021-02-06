#include "minishell.h"

void		ft_release_base(abs_struct *base)
{
	t_job	*j;
	t_job	*j_next;

	if (!base)
		return ;
	ft_array_release(base->env);
	ft_array_release(base->parseString);
	j = base->first_job;
	while ((j_next = ft_free_job(j))) 
		j = j_next;
	return ;
}

