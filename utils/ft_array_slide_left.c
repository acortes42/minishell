#include "minishell.h"

void		ft_array_slide_left(char **array)
{
	if (!array)
		return ;
	while (*array)
	{
		*array = *(array + 1);
		array++;
	}
}
