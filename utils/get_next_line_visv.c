/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:41:59 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:11:18 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_move_buffer_to_line(char *bf, char **line)
{
	char			*new_line;
	int				found_nl;

	new_line = ft_concat(*line, bf, &found_nl);
	free(*line);
	if (!new_line)
		return (-1);
	*line = new_line;
	ft_shift_left(bf);
	return (found_nl);
}

int	get_next_line(int fd, char **line)
{
	static char		bf[BUFFER_SIZE];
	int				proc;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	*line = ft_calloc(1, sizeof(char));
	if (!(*line))
		return (-1);
	proc = ft_move_buffer_to_line(bf, line);
	while (proc >= 0)
	{
		if (proc == 1)
			return (1);
		proc = read(fd, bf, BUFFER_SIZE);
		if (proc < 0)
			return (-1);
		if (!proc)
			return (0);
		if (proc < BUFFER_SIZE)
			bf[proc] = 0;
		proc = ft_move_buffer_to_line(bf, line);
	}
	free(*line);
	return (-1);
}
