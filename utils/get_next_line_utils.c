/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:45:34 by acortes-          #+#    #+#             */
/*   Updated: 2021/03/31 12:07:17 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strdup(const char *s1)
{
	int		x;
	char	*str;

	x = ft_strlen(s1) + 1;
	str = malloc(x * sizeof(char));
	if (!(str))
		return (NULL);
	while (x-- > 0)
		str[x] = s1[x];
	return (str);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		total;
	char	*str;
	int		n;

	total = ft_strlen(s2) + ft_strlen(s1) + 1;
	str = malloc(total * sizeof(char));
	if (!(str))
		return (NULL);
	n = 0;
	while (s1 && *s1)
		str[n++] = *s1++;
	while (s2 && *s2)
		str[n++] = *s2++;
	str[n] = '\0';
	return (str);
}

char	*ft_strcdup(const char *s1, int c)
{
	int		i;
	char	*str;
	char	car;

	i = 0;
	car = (char)c;
	while (s1[i] != car && s1[i] != '\0')
		i++;
	str = malloc(i + 1 * sizeof(char));
	str[i] = '\0';
	if (str == NULL)
	{
		return (NULL);
	}
	while (i-- > 0)
		str[i] = s1[i];
	return (str);
}

char	*ft_strchr(char *str, int c)
{
	int		i;
	char	str2;
	char	*x;

	str2 = (char)c;
	x = str;
	i = 0;
	while (x[i] != '\0' && x[i] != str2)
		i++;
	if (x[i] == str2)
		return (x + i);
	return (0);
}
