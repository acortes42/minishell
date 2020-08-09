/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_my_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 00:19:38 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/10 19:14:37 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_my_args(t_struct *base)
{
	if (base->take_arg == 1 && base->take_second_arg == 0)
		base->width = va_arg(base->va_lues, int);
	else if (base->take_arg == 0 && base->take_second_arg == 1)
		base->precision = va_arg(base->va_lues, int);
	else if (base->take_arg == 1 && base->take_second_arg == 1)
	{
		base->width = va_arg(base->va_lues, int);
		base->precision = va_arg(base->va_lues, int);
	}
	if (base->width < 0)
	{
		base->width *= -1;
		base->flags = 2;
	}
	if (base->precision < 0)
		base->start_precision = 0;
}
