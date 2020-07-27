/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 19:54:39 by acortes-          #+#    #+#             */
/*   Updated: 2019/12/14 16:54:42 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_next_line(int fd, char **line)
{
	static char	*s1[2024];
	char		*arr;
	char		buf[BUFFER_SIZE + 1];
	int			x;

	!(s1[fd]) ? s1[fd] = ft_strdup("") : 0;
	while ((x = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[x] = '\0';
		arr = ft_strjoin(s1[fd], buf);
		free(s1[fd]);
		if (ft_strchr((s1[fd] = arr), '\n'))
			break ;
	}
	if (x < 0 || line == NULL)
		return (-1);
	*line = ft_strcdup(s1[fd], '\n');
	arr = NULL;
	if (!(s1[fd][ft_strlen(*line)] == '\0'))
		arr = ft_strdup(ft_strchr(s1[fd], '\n') + 1);
	free(s1[fd]);
	return (s1[fd] = arr) == NULL ? 0 : 1;
}
