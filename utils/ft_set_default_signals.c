#include "minishell.h"

static int	set_signals_1()
{
	if (signal(SIGINT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	if (signal(SIGQUIT, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	if (signal(SIGTSTP, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	return (0);
}

static int 	set_signals_2()
{
	if (signal(SIGTTIN, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	if (signal(SIGTTOU, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	if (signal(SIGCHLD, SIG_DFL) == SIG_ERR)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	return (0);
}

int			ft_set_default_signals()
{
	int		ret;

	if ((ret = set_signals_1()))
		return (ret);
	if ((ret = set_signals_2()))
		return (ret);
	return (0);
}
