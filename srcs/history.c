/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:34 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:04:35 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int			ft_history(void)
{
	int		fd;
	int		num;
	char	**line;

	num = 1;
	line = malloc(sizeof((char**)line) * 1);
	fd = open("history.txt", O_RDWR);
	while (get_next_line(fd, line) > 0)
	{
		ft_putstr("\e[0m  ");
		ft_putnbr(num++);
		ft_putstr(" - ");
		ft_putstr(*line);
		ft_putstr("\n");
	}
	close(fd);
	return (1);
}
