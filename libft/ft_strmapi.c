/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:12:41 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:12:48 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*r;
	size_t			l;
	size_t			i;

	if (s == 0)
		return (0);
	l = ft_strlen(s);
	r = malloc(sizeof(char) * (l + 1));
	if (r == 0)
		return (0);
	i = 0;
	while (i < l)
	{
		r[i] = f(i, s[i]);
		i++;
	}
	r[l] = '\0';
	return (r);
}
