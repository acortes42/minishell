/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_s.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 18:31:22 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:33:24 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_s(t_struct *base)
{
	ft_my_args(base);
	if (!(base->x = va_arg(base->va_lues, char*)))
		base->x = "(null)";
	if (base->start_precision && base->precision < (int)ft_strlen(base->x))
		base->x = ft_strndup(base->x, base->precision);
	if (base->flags == 2)
		ft_put(base);
	if (base->width > (int)ft_strlen(base->x))
		while (base->n++ < base->width - (int)ft_strlen(base->x))
		{
			base->flags == 1 ? ft_putchar_fd('0') : ft_putchar_fd(' ');
			base->total_return++;
		}
	base->n = 0;
	if (base->flags != 2)
		ft_put(base);
	if (base->start_precision && base->precision < (int)ft_strlen(base->x))
		free(base->x);
}
