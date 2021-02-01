#include "minishell.h"

void		ft_release_base(abs_struct *base)
{
	if (!base)
		return ;
	ft_array_release(base->valid_str);
	ft_array_release(base->env);
	ft_array_release(base->parseString);
	free(base);
}
