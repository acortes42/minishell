/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_litostr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:09:06 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:17:55 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t			ft_numberlen(unsigned long int n, unsigned int base)
{
	size_t				s;

	s = 1;
	while (n >= base)
	{
		n = n / base;
		s++;
	}
	return (s);
}

char					*ft_litostr(long int n, int base,
	char lower_case)
{
	unsigned long int	ln;
	char				*digits;
	size_t				pos;
	char				*nstr;
	size_t				numberlen;

	pos = n < 0 ? 1 : 0;
	ln = (unsigned long int)(n < 0 ? -n : n);
	numberlen = pos + ft_numberlen(ln, (unsigned int)base);
	if (!(nstr = ft_calloc(numberlen + 1, sizeof(char))))
		return (0);
	digits = (lower_case ? "0123456789abcdef" : "0123456789ABCDEF");
	pos = numberlen - 1;
	while (ln >= (unsigned int)base)
	{
		nstr[pos--] = digits[(ln % base)];
		ln = ln / base;
	}
	nstr[pos] = digits[(ln % base)];
	if (pos)
		nstr[0] = '-';
	return (nstr);
}
