#include "minishell.h"

void	ft_execute_absolute_shell_command(t_abs_struct *base,
	char *cmd, t_process *p)
{
	execve(cmd, p->argv, base->env);
	if (errno == EACCES)
		p->status = 126;
	p->completed = 1;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}
