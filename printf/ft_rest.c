/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rest.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 01:04:03 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 17:42:05 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_rest(t_struct *base)
{
	if (base->flags == 2)
		ft_putchar_fd('%');
	if (base->width > 1)
		while (base->n++ < base->width - 1)
		{
			base->flags == 1 ? ft_putchar_fd('0') : ft_putchar_fd(' ');
			base->total_return++;
		}
	if (base->flags != 2)
		ft_putchar_fd('%');
	base->total_return++;
}
