#include "minishell.h"

void		ft_exit_minishell(abs_struct *base, int exit_code)
{
	ft_release_base(base);
	exit(exit_code);
}