#include "minishell.h"

int				ft_isempty(const char *s)
{
	const char	*t;

	if (!s)
		return (1);
	t = s;
	while (t)
	{
		if (!ft_isspace((int)*t))
			return (0);
		t++;
	}
	return (1);
}
