/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 14:16:35 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:16:55 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned char	*cd;
	unsigned char	*cs;
	size_t			i;

	cd = (unsigned char *)dest;
	cs = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		*cd = *cs;
		cd++;
		if (*cs == (unsigned char)c)
			return (cd);
		cs++;
		i++;
	}
	return (0);
}
