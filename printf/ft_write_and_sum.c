/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_and_sum.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 20:58:39 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:57:21 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_validate(char c)
{
	if ((c >= '0' && c <= '9') || c == '-' || c == '.' || c == '*')
		return (1);
	return (0);
}

void	play_the_numbers(t_struct *base, char *str, int n, int i)
{
	while (i < n)
	{
		if (str[i] == '0' && base->start_precision == 0 && base->width == 0\
			&& base->flags != 2)
			base->flags = 1;
		if (str[i] == '-' && base->width == 0 && base->start_precision == 0)
			base->flags = 2;
		if (str[i] >= '0' && str[i] <= '9' && base->start_precision == 0)
			base->width = (base->width * 10) + (str[i] - '0');
		if (str[i] == '.')
			base->start_precision += 1;
		if (str[i] >= '0' && str[i] <= '9' && base->start_precision == 1)
			base->precision = (base->precision * 10) + (str[i] - '0');
		if (str[i] == '*' && base->start_precision == 1 && base->precision == 0)
			base->take_second_arg += 1;
		if ((str[i] == '0' && base->precision > 0 && base->width > 0) &&\
			(ft_validate(str[i]) == 0))
		{
			base->start_precision += 3;
			break ;
		}
		if (str[i++] == '*' && base->start_precision == 0 && base->width == 0)
			base->take_arg += 1;
		base->len++;
	}
}

int		ft_trick(t_struct *base)
{
	int n;

	n = 0;
	while (base->copy[base->len + n] != '%' && ft_isalpha(base->copy
		[base->len + n]) != 1 && base->copy[base->len + n] != '\0')
		n++;
	return (n);
}

void	ft_second_trick(t_struct *base, char *str, int n)
{
	ft_putchar_fd('%');
	ft_putstr_fd(str);
	base->total_return += n + 1;
}

int		ft_write_and_sum(t_struct *base)
{
	char	*str;
	int		n;
	int		i;

	n = 0;
	i = 0;
	n = ft_trick(base);
	if (n == 0)
	{
		ft_new_me(base, base->copy[base->len]);
		return (0);
	}
	if (base->copy[base->len + n] == '\0')
		return (0);
	if (!(str = ft_strndup(base->copy + base->len, n)))
		return (0);
	play_the_numbers(base, str, n, i);
	if (base->start_precision <= 1 && base->take_arg <= 1 &&
			base->take_second_arg <= 1)
		ft_new_me(base, base->copy[base->len]);
	else
		ft_second_trick(base, str, n);
	free(str);
	return (0);
}
