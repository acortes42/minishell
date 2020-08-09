/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_u.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 02:36:07 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 19:03:33 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_itoa2(unsigned int nb)
{
	char		*str;
	long int	n;
	long int	i;

	n = nb;
	i = len(n);
	if (!(str = (char*)ft_calloc(sizeof(char), i + 1)))
		return (NULL);
	str[i] = '\0';
	str[0] = '0';
	while (i-- > 0)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}

void	ft_u(t_struct *base)
{
	ft_my_args(base);
	base->x = ft_itoa2(va_arg(base->va_lues, int));
	if (base->flags == 2)
	{
		ft_precision(base);
		ft_put(base);
		ft_width(base);
		free(base->x);
		return ;
	}
	ft_width(base);
	ft_precision(base);
	if (base->flags != 2)
		ft_put(base);
	free(base->x);
}
