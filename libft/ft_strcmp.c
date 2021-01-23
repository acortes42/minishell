/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:32:32 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:14:36 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int					ft_strcmp(const char *s1, const char *s2)
{
	size_t			i;
	unsigned char	*uc1;
	unsigned char	*uc2;

	uc1 = (unsigned char *)s1;
	uc2 = (unsigned char *)s2;
	i = 0;
	while (uc1 && uc2 && uc1[i] && uc2[i])
	{
		if (uc1[i] != uc2[i])
			return (uc1[i] - uc2[i]);
		i++;
	}
	if (!uc1 && !uc2)
		return (0);
	else if (!uc1)
		return (-1);
	else if (!uc2)
		return (1);
	else
		return (uc1[i] == uc2[i] ? 0 : (uc1[i] - uc2[i]));
}
