#include "minishell.h"

char	*ft_get_file_line(char *file, int line)
{
	char	*str;
	int		fd;
	int		curr_line;
	int		found_nl;

	if (!file || line < 0)
		return (0);
	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (0);
	curr_line = 0;
	str = 0;
	while (curr_line < (line - 1))
	{
		found_nl = classic_get_next(fd, &str);
		if (found_nl < 1)
			break ;
		curr_line++;
		if (str && curr_line < (line - 1))
		{
			free(str);
			str = 0;
		}
	}
	close(fd);
	if (curr_line < (line -1) && str)
	{
		free(str);
		str = 0;
	}
	return (str);
}
