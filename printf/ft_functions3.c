/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:02:21 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:58:44 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		len(long nb)
{
	int		len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		len++;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char		*str;
	long int	n;
	long int	i;

	n = nb;
	i = len(n);
	if (!(str = (char*)ft_calloc(sizeof(char), 1 + i)))
		return (NULL);
	str[i] = '\0';
	str[0] = '0';
	if (n < 0)
		n *= -1;
	while (i-- > 0)
	{
		str[i] = (n % 10) + '0';
		n = n / 10;
	}
	if (nb < 0)
		str[0] = '-';
	return (str);
}

void	ft_putchar_fd(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr_fd(int n)
{
	int x;

	x = 0;
	if (n == -2147483648)
	{
		write(1, "-", 1);
		write(1, "2147483648", 10);
		return ;
	}
	if (n < 0)
	{
		write(1, "-", 1);
		ft_putnbr_fd(n * (-1));
	}
	else
	{
		if (n >= 10)
			ft_putnbr_fd(n / 10);
		x = (n % 10) + '0';
		write(1, &x, 1);
	}
}

void	ft_putstr_fd(char *s)
{
	int i;

	i = 0;
	if (!(s))
		return ;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}
