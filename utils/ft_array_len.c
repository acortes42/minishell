#include "minishell.h"

size_t			ft_array_len(char **envp)
{
	size_t		l;

	l = 0;
	if (!envp)
		return (l);
	l = 0;
	while (*(envp + l))
		l++;
	return (l);
}
