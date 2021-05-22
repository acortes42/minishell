#include "minishell.h"

int	ft_isbuiltin(t_process *p)
{
	if (!p)
		return (0);
	else if ((!p->argv || !(*p->argv)))
	{
		return (p->ctrl_d);
	}
	else if (!ft_strcmp(p->argv[0], "env") || !ft_strcmp(p->argv[0], "unset")
		|| !ft_strcmp(p->argv[0], "export") || !ft_strcmp(p->argv[0], "exit")
		|| !ft_strcmp(p->argv[0], "echo") || !ft_strcmp(p->argv[0], "pwd")
		|| !ft_strcmp(p->argv[0], "cd") || !ft_strcmp(p->argv[0], "history")
		|| !ft_strcmp(p->argv[0], "help") || !ft_strcmp(p->argv[0], "clear"))
		return (1);
	return (0);
}
