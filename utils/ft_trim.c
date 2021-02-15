#include "minishell.h"

char			*ft_trim(char *str)
{
	size_t		start;
	size_t		end;
	char		*trimmed;

	if (!str || !(end = ft_strlen(str)))
		return (0);
	start = 0;
	while (ft_isspace(*(str + start)))
		start++;
	end--;
	while (start < end && ft_isspace(*(str + end)))
		end--;
	if (start >= end)
		return (0);
	if (!(trimmed = ft_calloc(end - start + 2, sizeof(char))))
		return (0);
	ft_memcpy(trimmed, str + start, (end - start + 1));
	return (trimmed);
}
