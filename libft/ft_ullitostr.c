/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ullitostr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:09:06 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:17:55 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t		ft_numberlen(unsigned long long int n, unsigned int base)
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

char				*ft_ullitostr(unsigned long long int n, int base,
	char lower_case)
{
	char			*digits;
	size_t			pos;
	char			*nstr;
	size_t			numberlen;

	numberlen = ft_numberlen(n, (unsigned int)base);
	if (!(nstr = ft_calloc(numberlen + 1, sizeof(char))))
		return (0);
	digits = (lower_case ? "0123456789abcdef" : "0123456789ABCDEF");
	pos = numberlen - 1;
	while (n >= (unsigned int)base)
	{
		nstr[pos--] = digits[(n % base)];
		n = n / base;
	}
	nstr[pos] = digits[(n % base)];
	return (nstr);
}
