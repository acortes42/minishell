#include "minishell.h"

t_job			*ft_build_jobs(char *command)
{
	char		*job_cmd;
	char		*cmd_i;
	t_job		*jobs;
	t_job		*job;

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
