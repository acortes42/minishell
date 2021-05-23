/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_input_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:53:20 by visv              #+#    #+#             */
/*   Updated: 2021/05/16 18:38:08 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	apply_input_redirection(int i_fd, char *right_side)
{
	int			o_fd;
	char		*fd_file;

	fd_file = ft_trim(right_side);
	if (!fd_file)
		return (0);
	if (!ft_strncmp(fd_file, "&-", 2))
	{
		close(i_fd);
		free(fd_file);
		return (1);
	}
	o_fd = ft_get_redirection_fd(fd_file, O_RDONLY, 0666, -1);
	if (o_fd < 0)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	dup2(o_fd, i_fd);
	if (*fd_file != '&' && o_fd >= 0)
		close(o_fd);
	free(fd_file);
	return (o_fd >= 0);
}

static void	dup_stdin_and_close_it(int i_fd)
{
	extern t_abs_struct	g_base;

	if (i_fd == STDIN_FILENO && g_base.std_fds.infile < 0)
	{
		g_base.std_fds.infile = dup(STDIN_FILENO);
		close(STDIN_FILENO);
	}
}

int	ft_input_redirection(char *redir, int *redirected)
{
	char			*fd;
	int				i_fd;
	int				found_redirection;

	found_redirection = 0;
	fd = 0;
	if (redir)
		fd = ft_split_shell_by(&redir, "<");
	if (redir && fd && *(redir - 1) == '<')
	{
		i_fd = ft_get_fd(fd, STDIN_FILENO);
		if (i_fd < 0)
			*redirected = 0;
		else
		{
			dup_stdin_and_close_it(i_fd);
			*redirected = apply_input_redirection(i_fd, redir);
		}
		found_redirection = 1;
	}
	if (fd)
		free(fd);
	return (found_redirection);
}
