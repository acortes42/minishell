#include "minishell.h"

int	ft_get_fd(char *redirection, int default_fd)
{
	if (ft_isempty(redirection))
		return (default_fd);
	if (ft_isinteger(redirection))
		return (ft_atoi(redirection));
	return (-1);
}

int	ft_get_redirection_fd(char *redirection, int flags,
	mode_t mode, int default_fd)
{
	extern t_abs_struct		g_base;
	char					*path;
	int						fd;
	int						i_fd;

	if (ft_isempty(redirection))
		return (default_fd);
	if ((*redirection == '&' && ft_isinteger(redirection + 1)) ||
		ft_isinteger(redirection))
		return (ft_atoi(redirection));
	path = ft_get_absolute_path(&g_base, redirection);
	if (!path)
		return (default_fd);
	fd = open(path, flags, mode);
	free(path);
	if (fd < 0)
		return (default_fd);
	else if (fd >= REDIRECTIONS_MINIMUM_FD)
		return (fd);
	i_fd = ft_get_first_fd_available_between(REDIRECTIONS_MINIMUM_FD, MAX_FD);
	if (i_fd >= REDIRECTIONS_MINIMUM_FD)
		dup2(fd, i_fd);
	close(fd);
	return (i_fd);
}
