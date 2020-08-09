/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_c.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 12:47:39 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 16:59:58 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_c(t_struct *base)
{
	char	x;
	int		n;

	n = 0;
	ft_my_args(base);
	x = va_arg(base->va_lues, int);
	if (base->flags == 2)
		ft_putchar_fd(x);
	while (n++ < base->width - 1)
	{
		base->flags == 1 ? ft_putchar_fd('0') : ft_putchar_fd(' ');
		base->total_return++;
	}
	if (base->flags != 2)
		ft_putchar_fd(x);
	base->total_return++;
	return ;
}
