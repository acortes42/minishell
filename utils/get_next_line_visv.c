/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_visv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:41:59 by vsempere          #+#    #+#             */
/*   Updated: 2021/04/21 15:12:31 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_move_buffer_to_line(char *bf, char **line)
{
	char			*new_line;
	int				found_nl;

	new_line = ft_concat(*line, bf, &found_nl);
	if (!new_line)
		return (-1);
	if (*line)
		free(*line);
	*line = new_line;
	ft_shift_left(bf);
	return (found_nl);
}

void	ft_erase(char **line)
{
	if (!line || !(*line))
		return ;
	ft_clear_input(ft_strlen(*line));
	free(*line);
	*line = 0;
}

static void load_previous_command(t_abs_struct *base, char **line, char *bf)
{
	int		fd;
	char	*history_line;

	if (!base->current_history_line)
		return ; // No hacemos nada cuando estamos al inicio
	fd = ft_open_history(base, O_RDWR);
	if (fd < 0)
		return ;
	base->current_history_line--;
	history_line = ft_get_file_line_by_fd(fd, base->current_history_line);
	close(fd);
	if (!history_line)
		return ;
	ft_erase(line);
	*line = history_line;
	ft_memset(bf, 0, BUFFER_SIZE);
	ft_putstr(*line);
}

static void load_next_command(t_abs_struct *base, char **line, char *bf)
{
	int		fd;
	char	*history_line;

	if (base->current_history_line >= base->history_lines)
	{ // Borramos el contenido, vaciamos el buffer y apuntamos el history
		ft_erase(line);
		ft_memset(bf, 0, BUFFER_SIZE);
		base->current_history_line = base->history_lines + 1;
		return ;
	}
	fd = ft_open_history(base, O_RDWR);
	if (fd < 0)
		return ;
	base->current_history_line++;
	history_line = ft_get_file_line_by_fd(fd, base->current_history_line);
	close(fd);
	if (!history_line)
		return ;
	ft_erase(line);
	*line = history_line;
	ft_memset(bf, 0, BUFFER_SIZE);
	ft_putstr(*line);
}

int	get_next_line(int fd, char **line, t_abs_struct *base)
{
	static char		bf[BUFFER_SIZE];
	int				proc;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	proc = ft_move_buffer_to_line(bf, line);
	while (proc >= 0)
	{
		if (proc == 1)
			return (1);
		proc = read(fd, bf, 4);
		if (proc < 0)
			break ;
		if (!proc)
			return (0);
		if (!ft_strcmp(ARROW_UP, bf))
			load_previous_command(base, line, bf);
		else if (!ft_strcmp(ARROW_DOWN, bf))
			load_next_command(base, line, bf);
		else
			ft_putstr(bf);
		proc = ft_move_buffer_to_line(bf, line);
	}
	if (*line)
		free(*line);
	*line = 0;
	return (-1);
}
