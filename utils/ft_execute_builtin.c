/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:52 by visv              #+#    #+#             */
/*   Updated: 2021/05/15 15:00:14 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_environment_builtins(t_abs_struct *base,
				 t_process *previous, t_process *p)
{
	int	executed;

	executed = 1;
	base->parse_string = p->argv;
	if (!ft_strcmp(p->argv[0], "env"))
	{
		if (set_redirections(base, p) < 0)
			return (0);
		ft_set_pipes(previous, p);
		ft_env(base);
	}
	else if (!ft_strcmp(p->argv[0], "unset"))
		ft_unset(base, p);
	else if (!ft_strcmp(p->argv[0], "export"))
		ft_export(base, p);
	else
		executed = 0;
	return (executed);
}

static void	launch_exit_builtin(char *exit_code)
{
	int	exit;

	ft_putstr("exit\n");
	if (exit_code)
		exit = ft_atoi(exit_code);
	else
		exit = 0;
	ft_exit_minishell(exit);
}

static int	execute_environment_builtins2(t_abs_struct *base,
	t_process *previous, t_process *p)
{
	if (!ft_strcmp(p->argv[0], "exit"))
		launch_exit_builtin(p->argv[1]);
	else if (!ft_strcmp(p->argv[0], "echo"))
	{
		if (set_redirections(base, p) < 0)
			return (0);
		ft_set_pipes(previous, p);
		ft_echo(base, p);
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "pwd"))
	{
		if (set_redirections(base, p) < 0)
			return (0);
		ft_set_pipes(previous, p);
		ft_pwd();
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "cd"))
	{
		cd(p);
		return (1);
	}
	return (0);
}

static int	execute_environment_builtins3(t_process *previous, t_process *p,
	t_abs_struct *base)
{
	if (!ft_strcmp(p->argv[0], "history"))
	{
		ft_set_pipes(previous, p);
		ft_history(base);
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "help"))
	{
		ft_set_pipes(previous, p);
		ft_help();
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "clear"))
	{
		ft_clear_screen();
		return (1);
	}
	return (0);
}

int	ft_execute_builtin(t_abs_struct *base, t_process *previous,
	t_process *p)
{
	int		executed;

	ft_putstr("\e[0m");
	if (!p->argv || !*p->argv)
	{
		if (p->ctrl_d)
			return (ft_execute_ctrl_d(base));
		return (1);
	}
	base->parse_string = p->argv;
	base->a = 0;
	executed = execute_environment_builtins(base, previous, p);
	if (!executed)
		executed = execute_environment_builtins2(base, previous, p);
	if (!executed)
		executed = execute_environment_builtins3(previous, p, base);
	return (executed);
}
