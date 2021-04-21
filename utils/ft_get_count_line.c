/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_count_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 19:25:51 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/21 11:48:24 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strsub2(char const *s, unsigned int start, size_t len)
{
	unsigned long int	o;
	char				*c;

	o = 0;
	c = malloc(len + 1);
	if (!s)
		return (0);
	if (c == 0)
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
	while ((*stat)[l] != '\n' && (*stat)[l] != '\0')
		l++;
	if ((*stat)[l] == '\n')
	{
		*line = ft_strsub2(*stat, 0, l);
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

int	ft_obtain_last(int fd, char **line)
{
	static char		*stat[2048];
	static int		ret;
	char			buff[2000];
	char			*temp;
	int				i;

	if (fd < 0 || line == NULL || read(fd, buff, 0) < 0)
		return (-1);
	i = read(fd, buff, 2000);
	while (i > 0)
	{
		buff[i] = '\0';
		if (stat[fd] == NULL)
			stat[fd] = ft_strdup(buff);
		else
		{
			temp = ft_strjoin(stat[fd], buff);
			free(stat[fd]);
			stat[fd] = temp;
		}
		if (ft_strchr(stat[fd], '\n'))
			break ;
	}
	ret++;
	if (end(stat, line, i, fd))
		ft_obtain_last(fd, line);
	return (ret);
}