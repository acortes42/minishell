/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_jobs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:30 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:17:33 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job			*ft_build_jobs(char *command)
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
	while ((job_cmd = ft_split_shell(&cmd_i)))
	{
		if (job)
		{
			if ((job->next = ft_build_job(job_cmd)))
				job = job->next;
		}
		else
		{
			jobs = ft_build_job(job_cmd);
			job = jobs;
		}
	}
	return (jobs);
}
