#include "minishell.h"

static int	execute_environment_builtins(abs_struct *base, t_process *p)
{
	int		executed;

	executed = 1;
	base->parseString = p->argv;
	if (!ft_strcmp(p->argv[0], "env"))
		ft_env(base);
	else if (!ft_strcmp(p->argv[0], "setenv"))
		ft_setenv(base, p);
	else if (!ft_strcmp(p->argv[0], "unsetenv"))
		ft_unsetenv(base, p);
	else if (!ft_strcmp(p->argv[0], "export"))
		ft_export(base, p);
	else
		executed = 0;
	return (executed);	
}

int         ft_execute_builtin(abs_struct *base, t_process *p)
{
	ft_putstr("\e[0m");
	if ((!p->argv || !*p->argv) && ft_execute_ctrl_d(base))
		return (1);
	if (execute_environment_builtins(base, p))
		return (1);
	if (!ft_strcmp(p->argv[0], "exit"))
		ft_exit_minishell(base, 0);
	else if (!ft_strcmp(p->argv[0], "echo"))
		echo(base);
	else if (!ft_strcmp(p->argv[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(p->argv[0], "cd"))
		cd(base);
	else if (!ft_strcmp(p->argv[0], "history"))
		ft_history();
	else if (!ft_strcmp(p->argv[0], "help"))
		ft_help(base);
	else if (!ft_strcmp(p->argv[0], "clear"))
		clearScreen();
	else
		return (0);
	return (1);
}