/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:26:35 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:26:40 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*uc;
	size_t			i;

	uc = (unsigned char *)s;
	i = 0;
	while (uc[i] && i < n && uc[i] != (unsigned char)c)
		i++;
	if (i < n && uc[i] == (unsigned char)c)
		return ((void *)s + i);
	return (0);
}
