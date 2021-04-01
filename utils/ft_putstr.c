/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 11:02:52 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 12:45:55 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr(char *s)
{
	int		i;

	i = 0;
	if (!(s))
		return ;
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void	ft_putnstr(char *s, size_t len)
{
	size_t	i;

	i = 0;
	if (!(s))
		return ;
	while (s[i] && i < len)
	{
		write(1, &s[i], 1);
		i++;
	}
}
