/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_i.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 12:11:28 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 17:44:32 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_width(t_struct *base)
{
	int n;
	int i;

	i = base->x[0] == '-' ? 1 : 0;
	n = (int)ft_strlen(base->x);
	while (base->width > n && base->width-- > base->precision + i)
	{
		base->flags == 1 && base->precision == 0 ?
			ft_putchar_fd('0') : ft_putchar_fd(' ');
		base->total_return++;
	}
	base->n = 0;
}

void	ft_precision(t_struct *base)
{
	int n;

	n = (int)ft_strlen(base->x);
	if (base->x[0] == '-')
		n--;
	if (base->precision > (int)ft_strlen(base->x))
		while (base->n++ < (base->precision - n))
		{
			ft_putchar_fd('0');
			base->total_return++;
		}
	base->n = 0;
}

void	ft_put(t_struct *base)
{
	if (base->x[0] == '0' && base->x[1] == '\0')
		if (base->start_precision == 1 && base->precision == 0)
		{
			if (base->width != 0)
			{
				ft_putchar_fd(' ');
				base->total_return++;
			}
			return ;
		}
	if (base->x[0] == '-')
		base->n++;
	while (base->x[base->n] != '\0')
	{
		ft_putchar_fd(base->x[base->n]);
		base->n++;
		base->total_return++;
	}
	base->n = 0;
}

void	ft_put2(t_struct *base)
{
	ft_putchar_fd('-');
	base->total_return++;
}

void	ft_i(t_struct *base)
{
	ft_my_args(base);
	base->x = ft_itoa(va_arg(base->va_lues, int));
	if (base->flags == 2)
	{
		if (base->x[0] == '-')
			ft_put2(base);
		ft_precision(base);
		ft_put(base);
		ft_width(base);
		free(base->x);
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
	free(base->x);
}
