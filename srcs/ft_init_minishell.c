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

static unsigned int	ft_getlflag(int fd)
{
	struct termios	settings;
	unsigned int	result;

	if (tcgetattr (fd, &settings) < 0)
	{
		perror ("error in tcgetattr");
		return (0);
	}
	result = settings.c_lflag;
	return (result);
}

int	ft_init_minishell(t_abs_struct *base, char **envp)
{
	char	termbuf[2048];
	char	*capbuf;

	if (!base)
		return (0);
	ft_memset(base, 0, sizeof(t_abs_struct));
	if (signal(SIGQUIT, signal_handler) == SIG_ERR)
		ft_exit_minishell(1);
	base->c_lflag = ft_getlflag(STDIN_FILENO);
	if (!ft_setlflag(STDIN_FILENO, 0, ICANON | ECHO | IEXTEN))
		ft_exit_minishell(1);
	tgetent(termbuf, "xterm-256color");
	ft_copy_env(base, envp);
	ft_init_history(base);
	capbuf = 0;
	base->arrow_up = tgetstr("ku", &capbuf);
	base->arrow_down = tgetstr("kd", &capbuf);
	if (capbuf)
		free(capbuf);
	return (1);
}
