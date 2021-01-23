/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:06:18 by vsempere          #+#    #+#             */
/*   Updated: 2019/12/12 14:03:34 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_memory_alloc(char ***r, size_t words)
{
	char			**n;
	size_t			i;

	n = (char **)ft_calloc(words + 1, sizeof(char *));
	if (n == 0)
		return (0);
	i = 0;
	while (i < words)
	{
		n[i] = (*r)[i];
		(*r)[i] = 0;
		i++;
	}
	if (*r != 0)
		free(*r);
	*r = n;
	return (1);
}

static void			ft_memory_release(char ***r)
{
	size_t			i;

	if (*r != 0)
	{
		i = 0;
		while ((*r)[i] != 0)
			free((*r)[i++]);
		free(*r);
		*r = 0;
	}
}

static char			**ft_split_internal(char const *s, char *delim2)
{
	char			**r;
	char			*p;
	char			*t;
	size_t			wc;

	wc = 0;
	r = (char **)ft_calloc(1, sizeof(char *));
	if (r == 0)
		return (0);
	p = (char *)s;
	while (p[0] != '\0' && (t = ft_strnstr(p, delim2, ft_strlen(p))) != 0)
	{
		if (p != t && (!ft_memory_alloc(&r, ++wc) ||
			!(r[wc - 1] = ft_substr(s, (p - s), (t - p)))))
		{
			ft_memory_release(&r);
			return (0);
		}
		p = t + 1;
	}
	if (p[0] != '\0' && (!ft_memory_alloc(&r, ++wc) ||
		!(r[wc - 1] = ft_substr(s, (p - s), ft_strlen(p)))))
		ft_memory_release(&r);
	return (r);
}

char				**ft_split(char const *s, char delim)
{
	char			**r;
	char			*delim2;

	if (s == 0)
		return (0);
	else if (s[0] == '\0')
		return ((char **)ft_calloc(1, sizeof(char *)));
	else
	{
		delim2 = ft_calloc(2, sizeof(char));
		if (!delim2)
			return (0);
		delim2[0] = delim;
		r = ft_split_internal(s, delim2);
		free(delim2);
		return (r);
	}
}
