/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_job.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:20 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 15:54:12 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job	*ft_build_job_ctrl_d(char *command)
{
	t_job		*j;

	j = ft_calloc(1, sizeof(t_job));
	if (!(j))
		return (0);
	j->command = command;
	j->std_fds.errfile = STDERR_FILENO;
	j->std_fds.infile = STDIN_FILENO;
	j->std_fds.outfile = STDOUT_FILENO;
	j->first_process = ft_build_ctrl_d_process();
	return (j);
}

t_job	*ft_build_job(char *command)
{
	t_job		*j;

	j = ft_calloc(1, sizeof(t_job));
	if (!command || !(*command) || !(j))
		return (0);
	j->command = command;
	j->std_fds.errfile = STDERR_FILENO;
	j->std_fds.infile = STDIN_FILENO;
	j->std_fds.outfile = STDOUT_FILENO;
	j->first_process = ft_build_processes(command);
	return (j);
}
