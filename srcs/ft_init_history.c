#include "minishell.h"

void	ft_init_history(t_abs_struct *base)
{
	int			fd;

	fd = ft_open_history(base, O_RDONLY);
	base->history_lines = ft_file_lines_by_fd(fd);
	if (fd >= 0)
		close(fd);
	fd = ft_open_history(base, O_RDONLY);
	base->last_history_command = ft_get_file_line_by_fd(fd,
			base->history_lines - 1);
	if (fd >= 0)
		close(fd);
	if (base->history_lines < 0)
		ft_exit_minishell(base, -1);
	base->current_history_line = base->history_lines;
}
