#include "minishell.h"

static char		*ft_expand_cmd(char *command)
{
	int			quote;
	char		*ptr;
	char		*output;

	if (!command)
		return (0);
	output = 0;
	ptr = command;
	quote = 0;
	while (*ptr)
	{
		(void)quote;
		(void)output;
		ptr++;
	}
	// TODO: Aquí hay que expandir los ${VARIABLE} y devolver la cadena expandida
	return (command);
}

t_job			*ft_build_job(char *command)
{
	t_job		*j;
	char		*cmd;

	if (!command || !(*command) || !(j = ft_calloc(1, sizeof(t_job))))
		return (0);
	j->command = command;
	// TODO: Parse command to redirect
	j->stderr = STDERR_FILENO;
	j->stdin = STDIN_FILENO;
	j->stdout = STDOUT_FILENO;
	cmd = ft_expand_cmd(command);
	j->first_process = ft_build_processes(cmd);
	return (j);
}
