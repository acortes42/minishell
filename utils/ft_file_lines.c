/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_file_lines.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:56:52 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/15 14:56:15 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_file_lines_by_fd(int fd)
{
	char	c;
	int		line_with_content;
	int		total_lines;
	int		read_ok;

	if (fd <= 0)
		return (0);
	line_with_content = 0;
	total_lines = 0;
	read_ok = 1;
	while (read_ok > 0)
	{
		read_ok = read(fd, &c, 1);
		if (read_ok <= 0)
			break ;
		line_with_content = 1;
		if (c == '\n')
		{
			line_with_content = 0;
			total_lines++;
		}
	}
	if (line_with_content)
		total_lines++;
	return (total_lines);
}

int	ft_file_lines(char *file)
{
	int		fd;
	int		total_lines;

	fd = open(file, O_RDONLY);
	total_lines = ft_file_lines_by_fd(fd);
	close(fd);
	return (total_lines);
}
