/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert_to_hex.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 04:28:13 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:58:05 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_to_hex(unsigned long int x)
{
	char				*str;
	unsigned long int	cpy;
	int					len;

	cpy = x;
	len = 0;
	if (x == 0)
		return ("0");
	while (cpy != 0)
	{
		cpy /= 16;
		len++;
	}
	if (!(str = (char*)ft_calloc(sizeof(char), len + 1)))
		return (NULL);
	while (len > 0)
	{
		len--;
		if (x % 16 <= 9)
			str[len] = x % 16 + '0';
		if (x % 16 > 9)
			str[len] = ((x % 16) + 7) + '0';
		x /= 16;
	}
	return (str);
}

char	*ft_strupcase(char *str)
{
	int count;

	count = 0;
	while (str[count] != '\0')
	{
		if (str[count] >= 97 && str[count] <= 122)
			str[count] = str[count] - 32;
		count++;
	}
	return (str);
}

int		ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) ||
		(c >= 97 && c <= 122))
		return (1);
	return (0);
}

int		ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

void	ft_width_p(t_struct *base)
{
	int n;
	int i;

	i = base->x[0] == '-' ? 1 : 0;
	if (base->start_precision != 0 && base->precision == 0)
		n = 2;
	else
		n = (int)ft_strlen(base->x) + 2;
	while (base->width > n && base->width-- > base->precision + i)
	{
		base->flags == 1 && base->precision == 0 ?
			ft_putchar_fd('0') : ft_putchar_fd(' ');
		base->total_return++;
	}
	base->n = 0;
}
