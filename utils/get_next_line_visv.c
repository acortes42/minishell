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

static int	print_new_line(char *bf)
{
	*bf = 0;
	ft_putstr("\n");
	return (1);
}

int	get_next_line(int fd, char **line, t_abs_struct *base)
{
	static char		bf[BUFFER_SIZE];
	int				proc;

	proc = ft_move_buffer_to_line(bf, line);
	while (fd >= 0 && BUFFER_SIZE >= 0 && proc >= 0)
	{
		if (proc == 1)
			return (1);
		proc = read(fd, bf, 2);
		if (proc < 0)
			break ;
		if (process_escape_sequences(bf, line, base))
			proc = 0;
		else if (*bf == '\n')
			return (print_new_line(bf));
		else
		{
			ft_putstr(bf);
			proc = ft_move_buffer_to_line(bf, line);
		}
	}
	if (*line)
		free(*line);
	*line = 0;
	return (-1);
}
