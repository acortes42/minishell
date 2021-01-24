#include "minishell.h"

void			ft_array_release(char **envp)
{
	char		**tmp;

	if (!envp)
		return ;
	tmp = envp;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(envp);
}

