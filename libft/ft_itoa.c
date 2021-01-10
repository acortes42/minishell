/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:09:06 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:17:55 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				*ft_itoa(int n2)
{
	long			n;
	char			r[11];
	int				sign;
	int				pos;
	char			*nstr;

	n = n2;
	pos = 10;
	sign = (n < 0 ? -1 : 1);
	while ((n >= 10 && sign > 0) || (n <= -10 && sign < 0))
	{
		r[pos] = '0' + ((sign < 0 ? -n : n) % 10);
		pos--;
		n = n / 10;
	}
	r[pos] = '0' + ((sign < 0 ? -n : n) % 10);
	if (sign < 0)
	{
		pos--;
		r[pos] = '-';
	}
	if (!(nstr = ft_calloc(11 - pos + 1, sizeof(char))))
		return (0);
	ft_memcpy(nstr, &r[pos], 11 - pos);
	return (nstr);
}
