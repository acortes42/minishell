/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_default_signals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:43 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:18:44 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		set_signals_1(void)
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

static int		set_signals_2(void)
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

int				ft_set_default_signals(void)
{
	int			ret;

	if ((ret = set_signals_1()))
		return (ret);
	if ((ret = set_signals_2()))
		return (ret);
	return (0);
}

void			forked_process_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\e[0m\n    Esto ha terminado con ctrl+c    \n");
		exit(0);
	}
}
