/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:56:35 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 13:56:38 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static unsigned int	ft_strcopy(char *t, unsigned int ti, char const *s)
{
	unsigned int	i;

	if (s == 0)
		return (ti);
	i = 0;
	while (s[i] != '\0')
	{
		t[ti] = s[i];
		ti++;
		i++;
	}
	return (ti);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t			l;
	size_t			ir;
	char			*r;

	l = 0;
	if (s1)
		l += ft_strlen(s1);
	if (s2)
		l += ft_strlen(s2);
	r = malloc(sizeof(char) * (l + 1));
	if (r == 0)
		return (0);
	ir = ft_strcopy(r, 0, s1);
	ft_strcopy(r, ir, s2);
	r[l] = '\0';
	return (r);
}
