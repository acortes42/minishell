/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:29:04 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:29:09 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*uc;

	uc = (unsigned char *)b;
	i = 0;
	while (len > 0 && i < len)
	{
		uc[i] = ((unsigned char)c);
		i++;
	}
	return (b);
}
