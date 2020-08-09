/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:00:06 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/10 21:03:27 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(const char *j)
{
	long int i[3];

	i[0] = 0;
	i[2] = 0;
	i[1] = 1;
	while (j[i[0]] == 32 || (j[i[0]] >= 9 && j[i[0]] <= 13))
		i[0]++;
	if (j[i[0]] < '0' && j[i[0]] > '9' && j[i[0]] != '-' && j[i[0]] != '+')
		return (0);
	if (j[i[0]] == '-' || j[i[0]] == '+')
	{
		if (j[i[0]] == '-')
			i[1] = (i[1] * (-1));
		i[0]++;
	}
	while (('9' >= j[i[0]]) && (j[i[0]] >= '0'))
	{
		i[2] = (i[2] * 10) + (j[i[0]] - '0');
		i[0]++;
		if (i[2] * i[1] > 2147483647)
			return (-1);
		else if (i[2] * i[1] < -2147483648)
			return (0);
	}
	return (i[2] * i[1]);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t i;

	i = 0;
	if (!(src && dst))
		return (0);
	if (dstsize > 0)
	{
		while (src[i] && (dstsize-- - 1) > 0)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen(src));
}

void	ft_bzero(void *str, size_t n)
{
	size_t			i;
	unsigned char	*x;

	i = 0;
	x = (unsigned char *)str;
	while (i < n)
		x[i++] = '\0';
}

void	*ft_calloc(size_t count, size_t size)
{
	void *str;

	if (!(str = malloc(count * size)))
		return (NULL);
	ft_bzero(str, count * size);
	return (str);
}
