/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 16:59:34 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:16:17 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *arr, ...)
{
	t_struct	*base;
	int			n;

	if (!(base = (t_struct*)ft_calloc(1, sizeof(t_struct))))
		return (-1);
	base->copy = (char*)arr;
	ft_all_values_to_start(base);
	if (arr)
	{
		va_start(base->va_lues, arr);
		base->len = ft_super_function(base);
		va_end(base->va_lues);
	}
	n = base->total_return;
	free(base);
	return (n);
}
