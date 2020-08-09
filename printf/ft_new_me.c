/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_new_me.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 11:54:35 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/10 20:11:24 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_new_me(t_struct *base, char c)
{
	if (c == 'c')
		ft_c(base);
	else if (c == 's')
		ft_s(base);
	else if (c == 'p')
		ft_p(base);
	else if (c == 'd')
		ft_d(base);
	else if (c == 'i')
		ft_i(base);
	else if (c == 'u')
		ft_u(base);
	else if (c == 'x')
		ft_x(base);
	else if (c == 'X')
		ft_big_x(base);
	else if (c == '%')
		ft_rest(base);
	else
	{
		ft_putchar_fd(c);
		base->total_return++;
	}
	return ;
}
