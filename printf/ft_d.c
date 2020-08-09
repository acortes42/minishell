/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_d.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:54:23 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:05:08 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_d(t_struct *base)
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
