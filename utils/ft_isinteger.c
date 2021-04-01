/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isinteger.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:07 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 14:24:42 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isinteger(char *str)
{
	char	*trimmed;
	char	*i;
	int		is_int;

	trimmed = ft_trim(str);
	if (!str || *str == '\0' || !(trimmed))
		return (0);
	i = trimmed;
	while (ft_isdigit(*i))
		i++;
	if (*i == '\0')
		is_int = 1;
	else
		is_int = 0;
	free(trimmed);
	return (is_int);
}
