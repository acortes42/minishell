/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:05:03 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:05:25 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void			ft_putchar_fd_st(char c, int fd)
{
	write(fd, &c, 1);
}

void				ft_putnbr_fd(int n, int fd)
{
	int				s;
	int				i;
	char			cn[11];
	int				nt;
	int				min;

	min = n == -2147483648 ? 1 : 0;
	i = 10;
	s = (n < 0 ? -1 : 1);
	nt = (min ? 2147483647 : n * s);
	while (i >= 0 && nt > 10)
	{
		cn[i] = ((nt % 10) + (s < 0 && min && i == 10 ? 1 : 0)) + '0';
		i--;
		nt = nt / 10;
	}
	cn[i--] = (nt % 10) + '0';
	cn[i] = (s < 0 ? '-' : '+');
	i += (s < 0 ? 0 : 1);
	while (i < 11)
		ft_putchar_fd_st(cn[i++], fd);
}
