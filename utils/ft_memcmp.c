/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:27:18 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:27:22 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int						ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t				i;
	unsigned char		*uc1;
	unsigned char		*uc2;

	uc1 = (unsigned char *)s1;
	uc2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (uc1[i] == uc2[i])
			i++;
		else
			return (uc1[i] - uc2[i]);
	}
	return (0);
}
