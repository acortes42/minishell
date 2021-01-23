/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:33:09 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:15:02 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t		i;
	size_t		j;

	i = 0;
	j = 0;
	if (little[0] == '\0' || !little)
		return ((char *)(big));
	while (big[i] && i < len)
	{
		while (big[i + j] == little[j] && (i + j) < len
			&& big[i + j])
			j++;
		if (little[j] == '\0')
			return ((char *)(big + i));
		j = 0;
		i++;
	}
	return (NULL);
}
