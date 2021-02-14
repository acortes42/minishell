#include "minishell.h"

t_process	*ft_release_process(t_process *p)
{
	t_process		*p_next;

	if (!p)
		return (0);
	p_next = p->next;
	p->next = 0;
	if (p->argv)
		ft_array_release(p->argv);
	free(p);
	return (p_next);
}
