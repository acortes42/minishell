/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_all_values_to_start.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:27:39 by acortes-          #+#    #+#             */
/*   Updated: 2019/12/12 18:41:14 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_all_values_to_start(t_struct *base)
{
	base->flags = 0;
	base->len = 0;
	base->width = 0;
	base->precision = 0;
	base->start_precision = 0;
	base->take_arg = 0;
	base->take_second_arg = 0;
	base->i = 0;
	base->n = 0;
	base->total_return = 0;
}
