#include "minishell.h"

void	load_previous_history_command(t_abs_struct *base, char **line,
	char *bf)
{
	int		fd;
	char	*history_line;
	char	*tmp;

	if (base->current_history_line <= 0)
		base->current_history_line = 0;
	else
		base->current_history_line--;
	fd = ft_open_history(base, O_RDONLY);
	if (fd < 0)
		return ;
	tmp = ft_get_file_line_by_fd(fd, base->current_history_line);
	history_line = ft_trim(tmp);
	if (tmp)
		free(tmp);
	if (fd)
		close(fd);
	if (!history_line)
		return ;
	ft_clear_input(line);
	*line = history_line;
	ft_memset(bf, 0, BUFFER_SIZE);
	ft_putstr(*line);
}

void	load_next_history_command(t_abs_struct *base, char **line, char *bf)
{
	int		fd;
	char	*history_line;

	if (base->current_history_line >= (base->history_lines - 1))
	{
		ft_clear_input(line);
		ft_memset(bf, 0, BUFFER_SIZE);
		base->current_history_line = base->history_lines;
		return ;
	}
	fd = ft_open_history(base, O_RDONLY);
	if (fd < 0)
		return ;
	base->current_history_line++;
	history_line = ft_get_file_line_by_fd(fd, base->current_history_line);
	close(fd);
	if (!history_line)
		return ;
	ft_clear_input(line);
	*line = history_line;
	ft_memset(bf, 0, BUFFER_SIZE);
	ft_putstr(*line);
}
