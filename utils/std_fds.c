/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 23:09:50 by visv              #+#    #+#             */
/*   Updated: 2021/03/31 12:04:27 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_std_fds(t_files_fd *fds)
{
	fds->infile = dup(STDIN_FILENO);
	fds->outfile = dup(STDOUT_FILENO);
	fds->errfile = dup(STDERR_FILENO);
}

void	restore_std_fds(t_files_fd *fds)
{
	if (fds->infile > -1)
	{
		dup2(fds->infile, STDIN_FILENO);
		close(fds->infile);
		fds->infile = -1;
	}
	if (fds->outfile > -1)
	{
		dup2(fds->outfile, STDOUT_FILENO);
		close(fds->outfile);
		fds->outfile = -1;
	}
	if (fds->errfile > -1)
	{
		dup2(fds->errfile, STDERR_FILENO);
		close(fds->errfile);
		fds->errfile = -1;
	}
}
