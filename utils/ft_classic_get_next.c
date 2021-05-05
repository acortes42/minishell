/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_classic_get_next.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 16:11:24 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/21 14:48:31 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	unsigned long int	o;
	char				*c;

	if (!s)
		return (0);
	o = 0;
	c = malloc(sizeof(char) * (len + 1));
	if (!c)
		return (0);
	if (start < ft_strlen(s))
	{
		while (o < len)
		{
			c[o] = s[start];
			start++;
			o++;
		}
	}
	c[o] = '\0';
	return (c);
}

static	int	finalline(char **stat, char **line)
{
	int				l;
	char			*c;

	l = 0;
	if (*line)
		free(*line);
	while ((*stat)[l] != '\n' && (*stat)[l] != '\0')
		l++;
	if ((*stat)[l] == '\n')
	{
		*line = ft_strsub(*stat, 0, l);
		c = ft_strdup(&((*stat)[l + 1]));
		free(*stat);
		*stat = c;
	}
	else
	{
		*line = ft_strdup(*stat);
		free(*stat);
		*stat = NULL;
		return (0);
	}
	return (1);
}

static	int	end(char **stat, char **line, int i, int fd)
{
	if (i < 0)
		return (-1);
	else if (i == 0 && stat[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	else
		return (finalline(&stat[fd], line));
}

int	classic_get_next(int fd, char **line, int clean_buffer)
{
	static char		*stat[2048];
	char			buff[BUFFER_SIZE + 1];
	char			*temp;
	int				i;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
		return (-1);
	i = read(fd, buff, BUFFER_SIZE);
	while (i > 0)
	{
		buff[i] = '\0';
		if (stat[fd] == NULL || clean_buffer)
		{
			if (clean_buffer)
				free(stat[fd]);
			stat[fd] = ft_strdup(buff);
		}
		else
		{
			temp = ft_strjoin(stat[fd], buff);
			free(stat[fd]);
			stat[fd] = temp;
		}
		if (ft_strchr(stat[fd], '\n'))
			break ;
		i = read(fd, buff, BUFFER_SIZE);
	}
	return (end(stat, line, i, fd));
}
