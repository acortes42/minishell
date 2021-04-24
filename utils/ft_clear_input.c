#include "minishell.h"

static int	ft_cmdlen(char *line)
{
	int		size;

	size = 0;
	while (line && *line)
	{
		if (*line == ESCAPE)
			line += 2;
		else
			size++;
		line++;
	}
	return (size);
}

void	ft_delete_chars(int len)
{
	char			*str;

	if (len <= 0)
		return ;
	str = ft_calloc((len * 3) + 1, sizeof(char));
	if (!str)
		return ;
	ft_memset(str, '\b', len);
	ft_memset(str + len, ' ', len);
	ft_memset(str + len + len, '\b', len);
	ft_putstr(str);
	free(str);
}

void	ft_clear_input(char **line)
{
	int				len;
	struct termios	settings;

	if (!line || !(*line))
		return ;
	if (tcgetattr (STDIN_FILENO, &settings) < 0)
		return ;
	len = ft_cmdlen(*line);
	ft_delete_chars(len);
	free(*line);
	*line = 0;
}
