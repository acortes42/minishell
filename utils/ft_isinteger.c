#include "minishell.h"

int			ft_isinteger(char *str)
{
	char	*trimmed;
	char	*i;
	int		is_int;

	if (!str || *str == '\0' || !(trimmed = ft_trim(str)))
		return (0);
	i = trimmed;
	while (ft_isdigit(*i))
		i++;
	is_int = (*i == '\0' ? 1 : 0);
	free(trimmed);
	return (is_int);
}
