#include "minishell.h"


t_job			*ft_build_jobs(char *command)
{
	char		**jobs_cmd;
	char		**jobs_i;
	t_job		*jobs;
	t_job		*job;

	if (!(jobs_cmd = ft_split(command, ';')))
		return (0);
	job = 0;
	jobs_i = jobs_cmd;
	while (*jobs_i)
	{
		if (job)
		{
			if ((job->next = ft_build_job(*jobs_i)))
				job = job->next;
		}
		else
		{
			jobs = ft_build_job(*jobs_i);
			job = jobs;
		}
		jobs_i++;
		free(*jobs_i);
	}
	free(jobs_cmd);
	return (jobs);
}
