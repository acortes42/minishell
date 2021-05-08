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

static void	ft_convert_tab_to_spaces(char *bf, int line_len)
{
	int		spaces;

	spaces = TAB_SPACES - (line_len % TAB_SPACES);
	while (spaces)
	{
		*bf = ' ';
		spaces--;
		bf++;
	}
}

static int	process_read_data(char *bf, char **line)
{
	if (*bf == '\n')
	{
		ft_memset(bf, 0, BUFFER_SIZE);
		ft_putstr("\n");
		return (1);
	}
	else if (*bf == CTRL_D)
	{
		ft_memset(bf, 0, BUFFER_SIZE);
		if (ft_strlen(*line) > 0)
			return (0);
		if (*line)
			free(*line);
		*line = 0;
		return (1);
	}
	else
	{
		if (!ft_strcmp(bf, "\t"))
			ft_convert_tab_to_spaces(bf, ft_strlen(*line));
		ft_putstr(bf);
		return (ft_move_buffer_to_line(bf, line));
	}
}

int	get_next_line(int fd, char **line, t_abs_struct *base)
{
	int				proc;

	proc = ft_move_buffer_to_line(base->input_bf, line);
	if (!proc)
	{
		while (fd >= 0 && BUFFER_SIZE >= 0)
		{
			proc = read(fd, base->input_bf, 2);
			if (proc < 0)
				break ;
			else if (proc > 0)
			{
				if (!process_escape_sequences(base->input_bf, line, base)
					&& process_read_data(base->input_bf, line))
					return (1);
			}
		}
	}
	if (*line)
		free(*line);
	*line = 0;
	return (-1);
}
