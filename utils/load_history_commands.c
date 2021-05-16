#include "minishell.h"

void	load_previous_history_command(t_abs_struct *base, char **line,
	char *bf)
{
	ft_memset(bf, 0, BUFFER_SIZE);
	if (!base->history || base->current_history_line <= 0)
	{
		base->current_history_line = 0;
		return ;
	}
	base->current_history_line--;
	ft_clear_input(line);
	*line = ft_trim(*(base->history + base->current_history_line));
	ft_putstr(*line);
}

void	load_next_history_command(t_abs_struct *base, char **line, char *bf)
{
	char	*history_line;

	ft_memset(bf, 0, BUFFER_SIZE);
	if (base->current_history_line >= (base->history_lines))
	{
		ft_clear_input(line);
		*line = ft_strdup("");
		base->current_history_line = base->history_lines;
		return ;
	}
	base->current_history_line++;
	history_line = ft_trim(*(base->history + base->current_history_line));
	if (!history_line)
		return ;
	ft_clear_input(line);
	*line = history_line;
	ft_putstr(*line);
}
