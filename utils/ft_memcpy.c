/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:27:51 by vsempere          #+#    #+#             */
/*   Updated: 2021/04/01 13:43:59 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t		i;
	char		*cd;
	char		*cs;

	if (dest == 0 && src == 0)
		return (0);
	i = 0;
	cd = (char *)dest;
	cs = (char *)src;
	while (i < n)
	{
		cd[i] = cs[i];
		i++;
	}
	return (dest);
}
