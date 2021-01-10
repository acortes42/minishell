/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:13:32 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:13:08 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_char_contained(char c, char const *set)
{
	int				i;

	i = 0;
	while (set[i] != '\0' && set[i] != c)
		i++;
	return (set[i] == c ? 1 : 0);
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

char				*ft_strtrim(char const *s1, char const *set)
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
	l = s == 0 && e == 0 ? l : l - s - (l - e - 1);
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