/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_functions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/10 21:01:23 by acortes-          #+#    #+#             */
/*   Updated: 2020/01/23 18:58:30 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strndup(const char *s, int n)
{
	int		i;
	char	*str;

	i = 0;
	if (n == 0)
		return ("");
	while (s[i] != '\0' && i < n - 1)
		i++;
	i += 1;
	if (!(str = (char*)ft_calloc(i + 1, sizeof(char))))
		return (NULL);
	while (i-- > 0)
		str[i] = s[i];
	return (str);
}

int		ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		return (c - 32);
	return (c);
}
