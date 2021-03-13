/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:52 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:17:53 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			execute_environment_builtins(t_abs_struct *base,
	t_process *previous, t_process *p)
{
	int				executed;

	executed = 1;
	base->parse_string = p->argv;
	if (!ft_strcmp(p->argv[0], "env"))
	{
		ft_set_pipes(previous, p);
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

static int			execute_environment_builtins2(t_abs_struct *base,
	t_process *previous, t_process *p)
{
	if (!ft_strcmp(p->argv[0], "exit"))
		ft_exit_minishell(base, 0);
	else if (!ft_strcmp(p->argv[0], "echo"))
	{
		ft_set_pipes(previous, p);
		echo(base, p);
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "pwd"))
	{
		ft_set_pipes(previous, p);
		ft_pwd();
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "cd"))
	{
		cd(base);
		return (1);
	}
	return (0);
}

static int			execute_environment_builtins3(t_abs_struct *base,
	t_process *previous, t_process *p)
{
	if (!ft_strcmp(p->argv[0], "history"))
	{
		ft_set_pipes(previous, p);
		ft_history();
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "help"))
	{
		ft_set_pipes(previous, p);
		ft_help(base);
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "clear"))
	{
		clear_screen();
		return (1);
	}
	return (0);
}

int					ft_execute_builtin(t_abs_struct *base, t_process *previous,
	t_process *p)
{
	ft_putstr("\e[0m");
	if ((!p->argv || !*p->argv) && ft_execute_ctrl_d(base))
		return (1);
	if (set_redirections(base, p))
		return (0);
	base->parse_string = p->argv;
	base->actual_argument = 0;
	if (execute_environment_builtins(base, previous, p))
		return (1);
	if (execute_environment_builtins2(base, previous, p))
		return (1);
	if (execute_environment_builtins3(base, previous, p))
		return (1);
	return (0);
}
