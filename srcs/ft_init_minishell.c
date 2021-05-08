/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:54:14 by visv              #+#    #+#             */
/*   Updated: 2021/05/01 16:00:04 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_quit_handler(int sig)
{
	extern t_abs_struct	g_base;

	if (sig == SIGINT)
	{
		ft_memset(g_base.input_bf, 0, BUFFER_SIZE);
		ft_clear_input(&g_base.input);
		ft_putstr("\n");
		ft_show_prompt(&g_base);
	}
	else
		ft_exit_minishell(&g_base, g_base.last_executed_process_status);
}

int	ft_init_minishell(t_abs_struct *base, char **envp)
{
	signal(SIGINT, process_quit_handler);
	signal(SIGQUIT, process_quit_handler);
	signal(SIGTSTP, process_quit_handler);
	signal(SIGTTIN, process_quit_handler);
	signal(SIGTTOU, process_quit_handler);
	signal(SIGKILL, process_quit_handler);
	if (!base)
		return (0);
	ft_memset(base, 0, sizeof(t_abs_struct));
	ft_copy_env(base, envp);
	ft_init_history(base);
	base->counter = 0;
	return (1);
}
