/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_visv.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:41:59 by vsempere          #+#    #+#             */
/*   Updated: 2021/05/01 16:26:55 by acortes-         ###   ########.fr       */
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

static void	load_previous_command(t_abs_struct *base, char **line, char *bf)
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

static void	load_next_command(t_abs_struct *base, char **line, char *bf)
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

int	ft_read_from_keyboard(char *bf, char **line, t_abs_struct *base, int fd)
{
	if (*bf == 127)
		ft_borrow_char(ft_strlen(*line), line, bf);
	else if (*bf == 27)
	{
		read(fd, bf, 1);
		if (*bf == 91)
		{
			read(fd, bf, 1);
			if (*bf == 65)
				load_previous_command(base, line, bf);
			else if (*bf == 66)
				load_next_command(base, line, bf);
		}
	}
	else if (*bf == 3)
	{
		ft_clear_input(line);
		ft_putstr("\n");
		ft_memset(bf, 0, BUFFER_SIZE);
		return (1);
	}
	else
		ft_putstr(bf);
	return (0);
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
		proc = read(fd, bf, 1);
		if (proc < 0)
			break ;
		if (!proc)
			return (0);
		if (ft_read_from_keyboard(bf, line, base, fd) == 1)
			return (1);
		proc = ft_move_buffer_to_line(bf, line);
	}
	if (*line)
		free(*line);
	*line = 0;
	return (-1);
}
