/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_restart_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:49:07 by acortes-          #+#    #+#             */
/*   Updated: 2019/12/08 18:57:08 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_restart_values(t_struct *base)
{
	base->flags = 0;
	base->width = 0;
	base->precision = 0;
	base->start_precision = 0;
	base->take_arg = 0;
	base->take_second_arg = 0;
	base->i = 0;
	base->n = 0;
}
