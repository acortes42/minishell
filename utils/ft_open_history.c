#include "minishell.h"

int	ft_open_history(t_abs_struct *base, int mode)
{
	char		*history_path;
	char		*home;
	int			fd;

	if (!base)
		return (-1);
//	home = getcwd(0, 0);
//	if (!home)
//		return (-1);
	home = ft_getenv(base->env, "HOME") + 5;
	if (home == 5)
		return (-1);
	history_path = ft_strjoin(home, "/history_visv.txt");
	//free(home);
	if (!history_path)
		return (-1);
	fd = open(history_path, mode | O_CREAT, S_IRUSR | S_IWUSR);
	free(history_path);
	return (fd);
}
