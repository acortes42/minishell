/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:54:14 by visv              #+#    #+#             */
/*   Updated: 2021/05/15 18:00:55 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_minishell(t_abs_struct *base, char **envp)
{
	char	termbuf[2048];
	char	*capbuf;

	tgetent(termbuf, "xterm-256color");
	signal(SIGQUIT, signal_handler);
	if (!base)
		return (0);
	ft_memset(base, 0, sizeof(t_abs_struct));
	ft_copy_env(base, envp);
	ft_init_history(base);
	capbuf = 0;
	base->arrow_up = tgetstr("ku", &capbuf);
	base->arrow_down = tgetstr("kd", &capbuf);
	if (capbuf)
		free(capbuf);
	return (1);
}
