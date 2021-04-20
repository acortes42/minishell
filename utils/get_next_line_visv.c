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
	struct termios	settings;
	int				result;
	size_t			len;
	size_t			erased;

	if (!line || !(*line))
		return ;
	result = tcgetattr (STDIN_FILENO, &settings);
	if (result < 0)
	{
		perror ("error in tcgetattr");
		return ;
	}
	len = ft_strlen(*line);
	erased = 0;
	while (erased < len)
	{
		ft_putstr((char *)(&settings.c_cc[VERASE]));
		erased++;
	}
	free(*line);
	*line = 0;
}

int	get_next_line(int fd, char **line)
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
			return (-1);
		if (!proc)
			return (0);
		if (!ft_strcmp(ARROW_UP, bf))
		{
			ft_erase(line);
			ft_memset(bf, 0, BUFFER_SIZE);
			proc = 0;
			*line = ft_strdup("ls -la");
			ft_putstr(*line);
		}
		else if (!ft_strcmp(ARROW_DOWN, bf))
		{
			ft_erase(line);
			ft_memset(bf, 0, BUFFER_SIZE);
			proc = 0;
			*line = ft_strdup("ls -d");
			ft_putstr(*line);
		}
		else
			ft_putstr(bf);
		if (proc < BUFFER_SIZE)
			bf[proc] = 0;
		proc = ft_move_buffer_to_line(bf, line);
	}
	free(*line);
	return (-1);
}
