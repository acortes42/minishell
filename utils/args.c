#include "minishell.h"

char	**get_first_non_empty_arg_pos(char **args)
{
	char	*trim;

	while (*args)
	{
		trim = ft_strtrim(*args, " \t");
		if (ft_strlen(trim))
		{
			free (trim);
			return (args);
		}
		if (trim)
			free(trim);
		args++;
	}
	return (0);
}

char	*get_first_non_empty_arg(char **args)
{
	char	*trim;

	while (*args)
	{
		trim = ft_strtrim(*args, " \t");
		if (ft_strlen(trim))
		{
			free (trim);
			return (*args);
		}
		if (trim)
			free(trim);
		args++;
	}
	return (0);
}
