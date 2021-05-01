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

static void	ft_init_history(t_abs_struct *base)
{
	int			fd;

	fd = ft_open_history(base, O_RDONLY);
	base->history_lines = ft_file_lines_by_fd(fd);
	if (fd >= 0)
		close(fd);
	if (base->history_lines < 0)
		ft_exit_minishell(base, -1);
	base->current_history_line = base->history_lines;
}

void	process_quit_handler(int sig)
{
	(void)sig;
	ft_setlflag(STDIN_FILENO, 1, ICANON | ECHO);
}

int	ft_init_minishell(t_abs_struct *base, char **envp)
{
	signal(SIGINT, process_quit_handler);
	signal(SIGQUIT, process_quit_handler);
	signal(SIGTSTP, process_quit_handler);
	signal(SIGTTIN, process_quit_handler);
	signal(SIGTTOU, process_quit_handler);
	if (!base)
		return (0);
	ft_memset(base, 0, sizeof(t_abs_struct));
	ft_copy_env(base, envp);
	ft_init_history(base);
	base->counter = 0;
	return (1);
}
