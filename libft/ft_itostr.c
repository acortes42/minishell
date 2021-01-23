/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itostr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:09:06 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:17:55 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_numberlen(long int n, int base)
{
	size_t			s;

	s = 1;
	while (n >= base)
	{
		n = n / base;
		s++;
	}
	return (s);
}

char				*ft_itostr(int n, int base, char lower_case,
	char group_with_thousands)
{
	long int		ln;
	char			*digits;
	size_t			pos;
	char			*nstr;
	size_t			numberlen;

	pos = n < 0 ? 1 : 0;
	ln = (n < 0 ? -(long int)n : n);
	numberlen = pos + ft_numberlen(ln, base);
	if (!(nstr = ft_calloc(numberlen +
		(!group_with_thousands ? 0 : numberlen % 3) + 1, sizeof(char))))
		return (0);
	digits = (lower_case ? "0123456789abcdef" : "0123456789ABCDEF");
	pos = numberlen - 1;
	while (ln >= base)
	{
		if (group_with_thousands && !(pos % 3) && pos != (numberlen - 1))
			nstr[pos--] = THOUSANDS_SEPARATOR;
		nstr[pos--] = digits[(ln % base)];
		ln = ln / base;
	}
	nstr[pos] = digits[(ln % base)];
	if (pos)
		nstr[0] = '-';
	return (nstr);
}
