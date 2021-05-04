/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:57:10 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/01 16:57:11 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	reset_str(int curr_line, int line, char **str)
{
	if (curr_line < line && *str)
	{
		free(*str);
		*str = 0;
	}
}

char	*ft_get_file_line_by_fd(int fd, int line)
{
	char	*str;
	int		curr_line;
	int		found_nl;

	if (fd < 0)
		return (0);
	curr_line = 0;
	str = 0;
	while (curr_line <= line)
	{
		found_nl = classic_get_next(fd, &str);
		if (found_nl < 1)
			break ;
		reset_str(curr_line, line, &str);
		curr_line++;
	}
	reset_str(curr_line, line, &str);
	return (str);
}

char	*ft_get_file_line(char *file, int line)
{
	char	*str;
	int		fd;

	if (!file || line < 0)
		return (0);
	fd = open(file, O_RDONLY);
	str = ft_get_file_line_by_fd(fd, line);
	close(fd);
	return (str);
}
