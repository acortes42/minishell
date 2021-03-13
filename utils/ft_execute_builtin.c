#include "minishell.h"

static int	execute_environment_builtins(t_abs_struct *base, t_process *previous, t_process *p)
{
	int		executed;

	executed = 1;
	base->parse_string = p->argv;
	if (!ft_strcmp(p->argv[0], "env"))
	{
		ft_set_pipes(previous,  p);
		ft_env(base);
	}
	else if (!ft_strcmp(p->argv[0], "setenv"))
		ft_setenv(base, p);
	else if (!ft_strcmp(p->argv[0], "unset"))
		ft_unset(base, p);
	else if (!ft_strcmp(p->argv[0], "export"))
		ft_export(base, p);
	else
		executed = 0;
	return (executed);	
}

int         ft_execute_builtin(t_abs_struct *base, t_process *previous, t_process *p)
{
	ft_putstr("\e[0m");
	if ((!p->argv || !*p->argv) && ft_execute_ctrl_d(base))
		return (1);
	if (set_redirections(base, p))
		return (0);
	// TODO: Utilizar la definición del proceso en lugar del parse_string y actual_argument
	base->parse_string = p->argv;
	base->actual_argument = 0;
	if (execute_environment_builtins(base, previous, p))
		return (1);
	if (!ft_strcmp(p->argv[0], "exit"))
		ft_exit_minishell(base, 0);
	else if (!ft_strcmp(p->argv[0], "echo"))
	{
		ft_set_pipes(previous, p);
		echo(base, p);
	}
	else if (!ft_strcmp(p->argv[0], "pwd"))
	{
		ft_set_pipes(previous, p);
		ft_pwd();
	}
	else if (!ft_strcmp(p->argv[0], "cd"))
		cd(base);
	else if (!ft_strcmp(p->argv[0], "history"))
	{
		ft_set_pipes(previous, p);
		ft_history();
	}
	else if (!ft_strcmp(p->argv[0], "help"))
	{
		ft_set_pipes(previous, p);
		ft_help(base);
	}
	else if (!ft_strcmp(p->argv[0], "clear"))
		clear_screen();
	else
		return (0);
	return (1);
}