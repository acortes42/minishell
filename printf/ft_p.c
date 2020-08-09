/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_p.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 02:30:13 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:40:11 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_precision_p(t_struct *base)
{
	int n;

	n = (int)ft_strlen(base->x);
	if (base->x[0] == '-')
		n--;
	if (base->precision > n)
		while (n + base->n++ < (base->precision))
		{
			ft_putchar_fd('0');
			base->total_return++;
		}
	base->n = 0;
}

void	ft_put_p(t_struct *base)
{
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

void	ft_25_line_norm(t_struct *base)
{
	ft_put_p(base);
	ft_precision_p(base);
}

void	tramp(t_struct *base)
{
	ft_precision_p(base);
	if (base->flags != 2)
		ft_put_p(base);
}

void	ft_p(t_struct *base)
{
	unsigned long int	n;

	ft_my_args(base);
	n = va_arg(base->va_lues, unsigned long int);
	if (!(base->x = ft_strlowcase(ft_convert_to_hex(n))))
		base->x = "";
	if (base->flags == 2)
	{
		ft_putstr_fd("0x");
		base->total_return += 2;
		if (!(base->start_precision == 1 && base->precision == 0))
			ft_25_line_norm(base);
		ft_width_p(base);
	}
	else
	{
		ft_width_p(base);
		ft_putstr_fd("0x");
		base->total_return += 2;
		if (!(base->start_precision == 1 && base->precision == 0))
			tramp(base);
	}
	ft_free(base, n);
}
