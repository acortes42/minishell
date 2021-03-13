/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_output_add_redirection.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:53:20 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 22:53:22 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		apply_output_redirection(t_abs_struct *base, char *fd,
	char *right_side)
{
	int			i_fd;
	int			o_fd;
	int			empty;
	char		*fd_file;

	empty = 0;
	if (!ft_isinteger(fd) && !(empty = ft_isempty(fd)))
		return (0);
	i_fd = empty ? STDOUT_FILENO : ft_atoi(fd);
	if (!(fd_file = ft_trim(right_side)))
		return (1);
	if (!ft_strncmp(fd_file, "&-", 2))
	{
		free(fd_file);
		return (close(i_fd));
	}
	if ((o_fd = open((fd_file + (*fd_file == '&' ? 1 : 0)),
		O_CREAT | O_TRUNC | O_WRONLY, 0666)) < 0)
		ft_exit_minishell(base, errno);
	if (dup2(o_fd, i_fd) < 0)
		ft_exit_minishell(base, errno);
	if (*fd_file != '&')
		close(o_fd);
	free(fd_file);
	return (0);
}

int				ft_output_redirection(t_abs_struct *base, char *redir,
	int *redirected)
{
	char		*fd;
	int			found_redirection;

	found_redirection = 0;
	fd = 0;
	if (redir &&
		(fd = ft_split_shell_by(&redir, ">")) && *(redir - 1) == '>')
	{
		*redirected = apply_output_redirection(base, fd, redir);
		found_redirection = 1;
	}
	if (fd)
		free(fd);
	return (found_redirection);
}
