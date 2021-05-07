/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:34 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/20 17:40:15 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_line(char *line)
{
	ft_putstr("\e[0m  ");
	ft_putstr(line);
	ft_putstr("\n");
}

static void	free_line(char **line)
{
	if (line && *line)
	{
		free(*line);
		*line = 0;
	}
}

int	ft_history(t_abs_struct *base)
{
	int		fd;
	char	*line;
	int		clean_buffer;

	line = 0;
	clean_buffer = 1;
	fd = ft_open_history(base, O_RDWR);
	if (fd <= 0)
		return (0);
	while (classic_get_next(fd, &line, clean_buffer) > 0)
	{
		clean_buffer = 0;
		write_line(line);
		free_line(&line);
	}
	free_line(&line);
	close(fd);
	return (1);
}
