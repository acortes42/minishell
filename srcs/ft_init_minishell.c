#include "minishell.h"

int				ft_init_minishell(abs_struct *base, char **envp)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	signal(SIGCHLD, SIG_IGN);

	if (!base)
		return (0);
	ft_memset(base, 0, sizeof(abs_struct));
	ft_copy_env(base, envp);
	return (1);
}