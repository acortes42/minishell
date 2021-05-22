/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:49 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/16 18:30:44 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	extern t_abs_struct	g_base;

	g_base.last_status = 128 + sig;
	if (sig == SIGINT)
	{
		g_base.last_status = 1;
		ft_memset(g_base.input_bf, 0, BUFFER_SIZE);
		if (g_base.input)
			free(g_base.input);
		g_base.input = 0;
		ft_putstr("\n");
		ft_show_prompt(&g_base);
	}
	else if (sig == SIGQUIT)
	{
		g_base.last_status = 0;
	}
}

void	forked_process_signal_handler(int sig)
{
	extern t_abs_struct		g_base;

	if (sig == SIGINT || sig == SIGQUIT)
	{
		g_base.last_status = 128 + sig;
		if (sig == SIGINT)
		{
			ft_putstr("\n");
			if (!g_base.current_process)
				g_base.last_status = 1;
		}
		else if (sig == SIGQUIT)
		{
			ft_putstr_fd("Abandona (`core' generado)\n", STDERR_FILENO);
			g_base.last_status = 0;
		}
	}
}
