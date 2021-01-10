/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:07:59 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:21:24 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_get_sign(const char *nptr, size_t *i)
{
	int			sign;

	sign = 1;
	while (nptr[*i] == '-' || nptr[*i] == '+')
	{
		if (nptr[*i] == '-')
			sign = -sign;
		(*i)++;
	}
	return (sign);
}

int				ft_atoi(const char *nptr)
{
	long int	ret;
	long int	prv;
	size_t		i;
	int			sign;
	char		overflow;

	i = 0;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	sign = ft_get_sign(nptr, &i);
	overflow = 0;
	ret = 0;
	while (!overflow && ft_isdigit((int)nptr[i]))
	{
		prv = ret;
		ret = (ret + (nptr[i] - '0')) * 10;
		overflow = prv > ret ? 1 : 0;
		i++;
	}
	if (!overflow)
		ret = (ret / 10) * sign;
	else
		ret = (sign < 0 ? 0 : -1);
	return (ret);
}
