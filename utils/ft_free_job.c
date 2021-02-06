#include "minishell.h"

static t_process	*ft_free_process(t_process *p)
{
	t_process		*p_next;

	if (!p)
		return (0);
	p_next = p->next;
	p->next = 0;
	if (p->argv)
		ft_array_release(p->argv);
	if (p->envp)
		ft_array_release(p->envp);
	free(p);
	return (p_next);
}

t_job				*ft_free_job (t_job *j)
{
	t_job			*j_next;
	t_process		*p;
	t_process		*p_next;

	if (!j)
		return (0);
	j_next = j->next;
	j->next = 0;
	p = j->first_process;
	while ((p_next = ft_free_process(p)))
		p = p_next;
	j->first_process = 0;
	if (j->command)
		free (j->command);
	free(j);
	return (j_next);
}
