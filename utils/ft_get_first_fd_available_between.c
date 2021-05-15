#include "minishell.h"

int	ft_get_first_fd_available_between(int minimum, int maximum)
{
	struct stat				s_stat;
	int						i_fd;

	i_fd = minimum;
	while (i_fd <= maximum)
	{
		if (fstat(i_fd, &s_stat) != -1)
			i_fd++;
		else
			return (i_fd);
	}
	return (-1);
}
