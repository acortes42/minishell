#include "minishell.h"

t_process			*ft_build_processes(char *expanded_cmd)
{
	t_process		*procs;
	t_process		*last_proc;
	char			*proc_cmd;

	procs = 0;
	last_proc = 0;
	while ((proc_cmd = ft_split_shell_by(&expanded_cmd, '|')))
	{
		if (!procs)
		{
			procs = ft_build_process(proc_cmd);
			last_proc = procs;
		}
		else
		{
			last_proc->next = ft_build_process(proc_cmd);
			last_proc = last_proc->next;
		}
		free(proc_cmd);
	}
	return (procs);
}
