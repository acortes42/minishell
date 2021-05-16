#include "minishell.h"

static int	ft_file_to_array(int fd, int lines_to_read, char ***history)
{
	int					line_num;
	int					added_lines;
	char				*line;

	line = 0;
	added_lines = 0;
	line_num = 0;
	while (line_num < lines_to_read)
	{
		classic_get_next(fd, &line, !line_num);
		if (!line)
			return (1);
		ft_array_add(history, &added_lines, ft_strdup(line));
		free(line);
		line = 0;
		line_num++;
	}
	return (1);
}

void	ft_init_history(t_abs_struct *base)
{
	int			fd;

	fd = ft_open_history(base, O_RDONLY | O_CREAT);
	if (fd >= 0)
	{
		base->history_lines = ft_file_lines_by_fd(fd);
		close(fd);
		fd = ft_open_history(base, O_RDONLY);
		if (fd >= 0)
		{
			ft_file_to_array(fd, base->history_lines, &base->history);
			close(fd);
		}
	}
	if (base->history_lines)
		base->last_history_command = ft_strdup(*(base->history
					+ base->history_lines - 1));
	if (base->history_lines < 0)
		ft_exit_minishell(-1);
	base->current_history_line = base->history_lines;
}
