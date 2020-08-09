/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_x.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 05:46:40 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:18:51 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strlowcase(char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
	{
		if (str[count] >= 65 && str[count] <= 90)
		{
			str[count] = str[count] + 32;
		}
		count++;
	}
	return (str);
}

void	ft_free(t_struct *base, int x)
{
	if (base->x != NULL && x != 0)
	{
		free(base->x);
		base->x = NULL;
	}
}

void	ft_x(t_struct *base)
{
	unsigned int x;

	x = 0;
	ft_my_args(base);
	x = va_arg(base->va_lues, unsigned int);
	base->x = ft_strlowcase(ft_convert_to_hex(x));
	if (base->flags == 2)
	{
		if (base->x[0] == '-')
			ft_put2(base);
		ft_precision(base);
		ft_put(base);
		ft_width(base);
		ft_free(base, x);
		return ;
	}
	if (base->x[0] == '-' && base->flags == 1 && base->precision == 0)
		ft_put2(base);
	ft_width(base);
	if (base->x[0] == '-' && !(base->flags == 1 && base->precision == 0))
		ft_put2(base);
	ft_precision(base);
	if (base->flags != 2)
		ft_put(base);
	ft_free(base, x);
}
