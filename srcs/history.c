/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:34 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/20 17:31:42 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_line(char *line)
{
	ft_putstr("\e[0m  ");
	ft_putstr(line);
	ft_putstr("\n");
}

int	ft_history(t_abs_struct *base)
{
	int		fd;
	int		num;
	char	*line;

	num = 1;
	line = 0;
	fd = open(ft_strjoin(base->env[8] + 4, "/history.txt"), O_RDWR);
	while (classic_get_next(fd, &line) > 0)
	{
		write_line(line);
		if (line)
		{
			free(line);
			line = 0;
		}
	}
	if (line)
	{
		free(line);
		line = 0;
	}
	close(fd);
	return (1);
}
