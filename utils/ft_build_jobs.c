/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:30 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 15:52:43 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_build_job_from_splitted_cmd(char *job_cmd, t_job **job)
{
	if (*job)
	{
		(*job)->next = ft_build_job(job_cmd);
		if ((*job)->next)
			*job = (*job)->next;
		else
			free(job_cmd);
	}
	else
	{
		*job = ft_build_job(job_cmd);
		if (!(*job))
			free(job_cmd);
	}
}

t_job	*ft_build_jobs(char *command)
{
	char		*job_cmd;
	char		*cmd_i;
	t_job		*jobs;
	t_job		*job;

	if (command && !(*command))
		return (ft_build_job_ctrl_d(command));
	jobs = 0;
	job = 0;
	cmd_i = command;
	job_cmd = ft_split_shell(&cmd_i);
	while (job_cmd)
	{
		if (!jobs)
		{
			ft_build_job_from_splitted_cmd(job_cmd, &jobs);
			job = jobs;
		}
		else
			ft_build_job_from_splitted_cmd(job_cmd, &job);
		job_cmd = ft_split_shell(&cmd_i);
	}
	return (jobs);
}
