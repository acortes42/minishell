#include "minishell.h"

void			ft_array_release(char **envp)
{
	char		**tmp;

	if (!envp)
		return ;
	tmp = envp;
	while (tmp)
	{
		if (*tmp)
			free(*tmp);
		tmp++;
	}
	free(tmp);
}

