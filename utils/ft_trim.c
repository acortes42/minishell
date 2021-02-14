#include "minishell.h"

char			*ft_trim(char *str)
{
	char			*i;

	if (!str)
		return (str);
	i = str + ft_strlen(str) - 1;
	while (i >= str && ft_isspace(*i))
	{
		*i = '\0';
		i--;
	}
	return (str);
}
