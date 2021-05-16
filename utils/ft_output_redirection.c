/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_redirection.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:53:20 by visv              #+#    #+#             */
/*   Updated: 2021/05/16 18:36:45 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	assign_to_fd_helper(char c)
{
	if (c == '&')
		return (1);
	else
		return (0);
}

void	redirect_to_exit(int o_fd, int i_fd)
{
	if (o_fd < 0)
		ft_exit_minishell(errno);
	dup2(o_fd, i_fd);
}

static int	apply_output_redirection(int i_fd, char *right_side)
{
	int			o_fd;
	char		*fd_file;
	int			flags;

	fd_file = ft_trim(right_side);
	if (!fd_file)
		return (0);
	if (!ft_strncmp(fd_file, "&-", 2))
	{
		free(fd_file);
		close(i_fd);
		return (1);
	}
	flags = O_CREAT | O_TRUNC | O_WRONLY;
	o_fd = ft_get_redirection_fd(fd_file, flags, 0666, -1);
	if (o_fd < 0)
	{
		free(fd_file);
		return (0);
	}
	redirect_to_exit(o_fd, i_fd);
	if (*fd_file != '&')
		close(o_fd);
	free(fd_file);
	return (1);
}

static void	dup_stdout_and_close_it(int i_fd, char *redir)
{
	extern t_abs_struct		g_base;

(void)redir;
	if (i_fd == STDOUT_FILENO)
	{
		g_base.std_fds.outfile = dup(STDOUT_FILENO);
		close(STDOUT_FILENO);
	}
}

int	ft_output_redirection(char *redir, int *redirected)
{
	char		*fd;
	int			i_fd;
	int			found_redirection;

	found_redirection = 0;
	*redirected = 0;
	fd = 0;
	if (redir)
		fd = ft_split_shell_by(&redir, ">");
	if (redir && fd && *(redir - 1) == '>')
	{
		i_fd = ft_get_fd(fd, STDOUT_FILENO);
		if (i_fd >= 0)
		{
			dup_stdout_and_close_it(i_fd, redir);
			*redirected = apply_output_redirection(i_fd, redir);
		}
		found_redirection = 1;
	}
	if (fd)
		free(fd);
	return (found_redirection);
}
