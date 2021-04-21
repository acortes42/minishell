#include "minishell.h"

int	ft_open_history(t_abs_struct *base, int mode)
{
	char	*history_path;
	char	*home;
	int		fd;

	if (!base)
		return (-1);
	home = ft_getenv(base->env, "HOME");
	if (!home)
		return (-1);
	history_path = ft_strjoin(home + 5, "/.history");
	if (!history_path)
		return (-1);
	fd = open(history_path, mode);
	free(history_path);
	return (fd);
}
