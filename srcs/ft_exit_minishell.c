#include "minishell.h"

void		ft_exit_minishell(t_abs_struct *base, int exit_code)
{
	if (exit_code && errno != 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	ft_release_base(base);
	exit(exit_code);
}