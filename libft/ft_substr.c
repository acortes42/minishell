/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 13:57:29 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 13:57:58 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*ret;
	size_t			l;
	size_t			size;

	l = s == 0 ? 0 : ft_strlen(s);
	if (!l || start >= l)
		return (ft_calloc(1, sizeof(char)));
	size = (l - start + 1) < len ? (l - start) : len;
	if (!(ret = (char *)ft_calloc(size + 1, sizeof(char))))
		return (0);
	ft_strlcat(ret, s + start, size + 1);
	return (ret);
}
