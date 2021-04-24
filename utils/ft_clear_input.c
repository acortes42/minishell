#include "minishell.h"

static int	ft_cmdlen(char *line)
{
	// TODO: Ojo con los comandos de mas de 1 byte... ctrl + ...
	// Son los que hacen que al navegar por el historial se borre más de la cuenta
	return ft_strlen(line);
}

void	ft_clear_input(char **line)
{
	int				len;
	char			*str;
	struct termios	settings;

	if (!line || !(*line))
		return ;
	if (tcgetattr (STDIN_FILENO, &settings) < 0)
		return ;
	len = ft_cmdlen(*line);
	str = ft_calloc((len * 3) + 1, sizeof(char));
	if (!str)
		return ;
	ft_memset(str, '\b', len);
	ft_memset(str + len, ' ', len);
	ft_memset(str + len + len, '\b', len);
	ft_putstr(str);
	free(str);
	free(*line);
	*line = 0;
}
