/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:49 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:50:39 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signal_handler(int sig)
{
	extern t_abs_struct	g_base;

	if (sig == SIGINT)
	{
		ft_memset(g_base.input_bf, 0, BUFFER_SIZE);
		ft_clear_input(&g_base.input);
		ft_putstr("\n");
		ft_show_prompt(&g_base);
		g_base.last_executed_process_status = 130;
	}
	else if (sig == SIGQUIT)
	{
		ft_exit_minishell(&g_base, 128 + sig);
	}
}

void	forked_process_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr("\n");
		exit(130);
	}
}
