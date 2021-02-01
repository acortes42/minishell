#include "minishell.h"

void		ft_exit_minishell(abs_struct *base)
{
	ft_release_base(base);
	exit(0);
}