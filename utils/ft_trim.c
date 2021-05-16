/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:11:09 by visv              #+#    #+#             */
/*   Updated: 2021/05/16 18:35:50 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_trim(char *str)
{
	size_t		start;
	size_t		end;
	char		*trimmed;

	end = ft_strlen(str);
	if (!str || !(end))
		return (0);
	start = 0;
	while (ft_isspace(*(str + start)))
		start++;
	end--;
	while (start < end && ft_isspace(*(str + end)))
		end--;
	if (start > end)
		start = end;
	trimmed = ft_calloc(end - start + 2, sizeof(char));
	if (!(trimmed))
		return (0);
	ft_memcpy(trimmed, str + start, (end - start + 1));
	return (trimmed);
}

static int	ft_char_contained(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0' && set[i] != c)
		i++;
	if (set[i] == c)
		return (1);
	return (0);
}

static unsigned int	ft_strtrim_start_index(char const *s, char const *set)
{
	unsigned int	i;

	i = 0;
	while (s != 0 && s[i] != '\0' && ft_char_contained(s[i], set))
		i++;
	return (i);
}

static unsigned int	ft_strtrim_end_index(char const *s, char const *set,
		unsigned int start_index)
{
	unsigned int	i;
	unsigned int	l;

	l = ft_strlen(s);
	i = l - 1;
	while (s != 0 && ft_char_contained(s[i], set) && i > start_index)
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	l;
	unsigned int	i;
	unsigned int	s;
	unsigned int	e;
	char			*r;

	if (s1 == 0)
		return (0);
	l = ft_strlen(s1);
	if (l <= 0)
		return ((char *)s1);
	s = ft_strtrim_start_index(s1, set);
	e = ft_strtrim_end_index(s1, set, s);
	l = s == 0 && e == 0 ? 1 : l - s - (l - e - 1);
	r = malloc((sizeof(char) * l) + 1);
	if (r == 0)
		return (0);
	i = 0;
	while ((s + i) <= e)
	{
		r[i] = s1[s + i];
		i++;
	}
	r[l] = '\0';
	return (r);
}
