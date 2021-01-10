/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:28:26 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:28:32 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dest, const void *src, size_t len)
{
	char	*cd;
	char	*cs;
	size_t	i;

	if (dest == NULL && src == NULL)
		return (NULL);
	cd = (char *)dest;
	cs = (char *)src;
	i = 0;
	if (src > dest)
		while (i < len)
		{
			cd[i] = cs[i];
			i++;
		}
	else
		while (len > 0)
		{
			len--;
			cd[len] = cs[len];
		}
	return (dest);
}
