/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:09:50 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 23:09:52 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			dup_std_fds(t_files_fd *fds)
{
	fds->infile = dup(STDIN_FILENO);
	fds->outfile = dup(STDOUT_FILENO);
	fds->errfile = dup(STDERR_FILENO);
}

void			restore_std_fds(t_files_fd *fds)
{
	if (fds->infile > -1 && fds->infile != STDIN_FILENO)
	{
		dup2(fds->infile, STDIN_FILENO);
		close(fds->infile);
	}
	if (fds->outfile > -1 && fds->outfile != STDOUT_FILENO)
	{
		dup2(fds->outfile, STDOUT_FILENO);
		close(fds->outfile);
	}
	if (fds->errfile > -1 && fds->errfile != STDERR_FILENO)
	{
		dup2(fds->errfile, STDERR_FILENO);
		close(fds->errfile);
	}
}
