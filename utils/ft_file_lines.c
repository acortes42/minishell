#include "minishell.h"

int	ft_file_lines(char *file)
{
	int		fd;
	char	c;
	int		lines;
	int		read_ok;

	fd = open(file, O_RDONLY);
	if (fd <= 0)
		return (0);
	lines = 0;
	read_ok = 1;
	while (read_ok > 0)
	{
		read_ok = read(fd, &c, 1);
		if (read_ok > 0 && c == '\n')
			lines++;
	}
	close(fd);
	return (lines);
}
