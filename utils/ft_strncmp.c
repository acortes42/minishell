/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:32:32 by vsempere          #+#    #+#             */
/*   Updated: 2021/04/01 12:11:39 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*uc1;
	unsigned char	*uc2;

	uc1 = (unsigned char *)s1;
	uc2 = (unsigned char *)s2;
	i = 0;
	while ((uc1[i] || uc2[i]) && i < n)
	{
		if (uc1[i] != uc2[i])
			return (uc1[i] - uc2[i]);
		i++;
	}
	return (0);
}
