#include "minishell.h"

t_job			*ft_build_job(char *command)
{
	t_job		*j;

	if (!command || !(*command) || !(j = ft_calloc(1, sizeof(t_job))))
		return (0);
	j->command = command;
	j->std_fds.errfile = STDERR_FILENO;
	j->std_fds.infile = STDIN_FILENO;
	j->std_fds.outfile = STDOUT_FILENO;
	j->first_process = ft_build_processes(command);
	return (j);
}
