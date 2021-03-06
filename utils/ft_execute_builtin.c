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

static int	execute_environment_builtins(t_abs_struct *base, t_process *p)
{
	int	executed;

	executed = 1;
	base->parse_string = p->argv;
	if (!ft_strcmp(p->argv[0], "env"))
		ft_env(base, p);
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

	ft_putstr_fd("exit\n", STDERR_FILENO);
	if (exit_code)
	{
		if (exists_non_digits_chars(exit_code))
		{
			ft_putstr_fd("Numeric argument required\n", STDERR_FILENO);
			exit = 255;
		}
		else
			exit = ft_atoi(exit_code);
	}
	else
		exit = 0;
	exit = ft_adjust_exit_value(exit);
	ft_exit_minishell(exit);
}

static int	execute_environment_builtins2(t_process *p)
{
	if (!ft_strcmp(p->argv[0], "exit"))
		launch_exit_builtin(p->argv[1]);
	else if (!ft_strcmp(p->argv[0], "echo"))
	{
		ft_echo(p);
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "pwd"))
		return (ft_pwd());
	else if (!ft_strcmp(p->argv[0], "cd"))
		return (!cd(p));
	return (0);
}

static int	execute_environment_builtins3(t_process *p, t_abs_struct *base)
{
	if (!ft_strcmp(p->argv[0], "history"))
	{
		ft_history(base);
		return (1);
	}
	else if (!ft_strcmp(p->argv[0], "help"))
	{
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

int	ft_execute_builtin(t_abs_struct *base, t_process *p)
{
	int		executed;

	if (!p->argv || !*p->argv)
	{
		if (p->ctrl_d)
			return (ft_execute_ctrl_d(base));
		return (1);
	}
	base->parse_string = p->argv;
	base->a = 0;
	executed = execute_environment_builtins(base, p);
	if (!executed)
		executed = execute_environment_builtins2(p);
	if (!executed)
		executed = execute_environment_builtins3(p, base);
	return (executed);
}
