/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:34 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:55:48 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	write_line(int num, char *line)
{
	ft_putstr("\e[0m  ");
	ft_putnbr(num++);
	ft_putstr(" - ");
	ft_putstr(line);
	ft_putstr("\n");
}

int	ft_history(void)
{
	int		fd;
	int		num;
	char	*line;

	num = 1;
	line = 0;
	fd = open("history.txt", O_RDWR);
	while (get_next_line(fd, &line) > 0)
	{
		write_line(num, line);
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
