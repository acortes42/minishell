/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:49 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/08 20:27:11 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	extern t_abs_struct	g_base;

	g_base.error = 128 + sig;
	if (sig == SIGINT)
	{
		ft_memset(g_base.input_bf, 0, BUFFER_SIZE);
		if (g_base.input)
			free(g_base.input);
		g_base.input = 0;
		ft_putstr("\n");
		ft_show_prompt(&g_base);
	}
	else if (sig == SIGQUIT)
	{
		ft_exit_minishell(g_base.error);
	}
}

void	forked_process_signal_handler(int sig)
{
	if (sig == SIGINT || sig == SIGQUIT)
	{
		if (sig == SIGINT)
			ft_putstr("\n");
		exit(128 + sig);
	}
}
