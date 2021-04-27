#include "minishell.h"

int	ft_file_lines_by_fd(int fd)
{
	char	c;
	int		line_with_content;
	int		lines;
	int		read_ok;

	if (fd <= 0)
		return (0);
	line_with_content = 0;
	lines = 0;
	read_ok = 1;
	while (read_ok > 0)
	{
		read_ok = read(fd, &c, 1);
		if (read_ok > 0)
		{
			line_with_content = 1;
			if (c == '\n')
			{
				line_with_content = 0;
				lines++;
			}
		}
	}
	if (line_with_content)
		lines++;
	return (lines);
}

int	ft_file_lines(char *file)
{
	int		fd;
	int		lines;

	fd = open(file, O_RDONLY);
	lines = ft_file_lines_by_fd(fd);
	close(fd);
	return (lines);
}
