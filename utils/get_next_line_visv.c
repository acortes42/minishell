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
	*line = 0;
}

int	get_next_line(int fd, char **line, t_abs_struct *base)
{
	static char		bf[BUFFER_SIZE];
	int				proc;
	int				x;
	char			*buf_line;
	int				fd2;

	if (fd < 0 || BUFFER_SIZE <= 0 || !line)
		return (-1);
	proc = ft_move_buffer_to_line(bf, line);
	x = 0;
	while (proc >= 0)
	{
		fd2 = open(ft_strjoin(base->env[8] + 4, "/history.txt"), O_RDWR);
		if (proc == 1)
			return (1);
		proc = read(fd, bf, 4);
		if (proc < 0)
			return (-1);
		if (!proc)
			return (0);
		/* No acabo de hacerlo funcionar, por lo que implemente una version muy simple que solo
			 busca los dos ultimos valores del historial. Debe ser un fallo bastante tonto, pero no lo veo.*/
		if (!ft_strcmp(ARROW_UP, bf))
		{
			ft_erase(line);
			ft_memset(bf, 0, BUFFER_SIZE);
			proc = 1;
			if (x < 2)
				*line = ft_strdup(ft_get_correct_line(fd2, &buf_line, base->last_line - ++x));
			ft_putstr(*line);
		}
		else if (!ft_strcmp(ARROW_DOWN, bf))
		{
			ft_erase(line);
			ft_memset(bf, 0, BUFFER_SIZE);
			proc = 0;
			if (x > 0)
				*line = ft_strdup(ft_get_correct_line(fd2, &buf_line, base->last_line - --x));
			ft_putstr(*line);
		}
		else
			ft_putstr(bf);
		if (!ft_strcmp(ARROW_DOWN, bf) || !ft_strcmp(ARROW_UP, bf))
			x = 0;
		if (proc < BUFFER_SIZE)
			bf[proc] = 0;
		proc = ft_move_buffer_to_line(bf, line);
		close(fd2);
	}
	free(*line);
	return (-1);
}
