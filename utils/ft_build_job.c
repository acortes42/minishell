#include "minishell.h"

static char		*ft_expand_cmd(abs_struct *base)
{
	if (!base->string)
		return (0);
	// TODO: Aquí hay que expandir los ${VARIABLE} y devolver la cadena expandida
	return base->string;
}

t_job			*ft_build_job(abs_struct *base)
{
	t_job		*j;
	char		*cmd;

	if (!(j = ft_calloc(1, sizeof(t_job))))
		return (0);
	j->command = ft_strdup(base->string);
	// TODO: Parse command to redirect
	j->stderr = STDERR_FILENO;
	j->stdin = STDIN_FILENO;
	j->stdout = STDOUT_FILENO;
	cmd = ft_expand_cmd(base);
	j->first_process = ft_build_processes(cmd);
	return (j);
}
