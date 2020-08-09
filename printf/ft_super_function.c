/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_super_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 12:44:27 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 19:04:36 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_super_function(t_struct *base)
{
	if (ft_strchr(base->copy, '%') == 0)
	{
		ft_putstr_fd(base->copy);
		base->total_return = (int)ft_strlen(base->copy);
		return (0);
	}
	if (ft_strlen(base->copy) == 1 && ft_strchr(base->copy, '%') != 0)
		return (0);
	while (base->copy[base->len] != '\0')
	{
		base->total_return++;
		if (base->copy[base->len] == '%')
		{
			base->len++;
			base->total_return--;
			ft_restart_values(base);
			ft_write_and_sum(base);
		}
		else
			ft_putchar_fd(base->copy[base->len]);
		base->len++;
	}
	return (0);
}
