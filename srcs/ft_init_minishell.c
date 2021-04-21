/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:54:14 by visv              #+#    #+#             */
/*   Updated: 2021/04/21 14:45:27 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_minishell(t_abs_struct *base, char **envp)
{
	int	fd2;
	char	*buf_line;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	if (!base)
		return (0);
	ft_memset(base, 0, sizeof(t_abs_struct));
	ft_copy_env(base, envp);
	if (!(base->last_line))
	{
		fd2 = open(ft_strjoin(base->env[8] + 4, "/history.txt"), O_RDWR);
		base->last_line = ft_obtain_last(fd2, &buf_line);
		close(fd2);
		free(buf_line);
	}
	base->counter = 0;
	return (1);
}
