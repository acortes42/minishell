/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:30:48 by vsempere          #+#    #+#             */
/*   Updated: 2019/12/12 14:13:45 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;

	i = ft_strnlen(dst, size);
	j = 0;
	if (size)
	{
		while (src[j] && i < (size - 1))
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		if (i < size)
			dst[i] = '\0';
	}
	i += ft_strlen(&src[j]);
	return (i);
}
