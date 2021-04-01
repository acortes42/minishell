/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:09:06 by vsempere          #+#    #+#             */
/*   Updated: 2021/04/01 14:22:05 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long	value_of_r_pos(int sign, long n)
{
	if ('0' + (sign < 0))
		return (-n % 10);
	else
		return (n % 10);
}

char	*ft_itoa(int n2)
{
	long			n;
	char			r[11];
	int				sign;
	int				pos;
	char			*nstr;

	n = n2;
	pos = 10;
	sign = 1;
	if (n < 0)
		sign = -1;
	while ((n >= 10 && sign > 0) || (n <= -10 && sign < 0))
	{
		r[pos] = value_of_r_pos(sign, n);
		pos--;
		n = n / 10;
	}
	r[pos] = value_of_r_pos(sign, n);
	if (sign < 0)
		r[--pos] = '-';
	nstr = ft_calloc(11 - pos + 1, sizeof(char));
	if (!(nstr))
		return (0);
	ft_memcpy(nstr, &r[pos], 11 - pos);
	return (nstr);
}
