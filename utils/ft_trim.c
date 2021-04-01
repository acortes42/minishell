/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_trim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:11:09 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 11:50:03 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_trim(char *str)
{
	size_t		start;
	size_t		end;
	char		*trimmed;

	end = ft_strlen(str);
	if (!str || !(end))
		return (0);
	start = 0;
	while (ft_isspace(*(str + start)))
		start++;
	end--;
	while (start < end && ft_isspace(*(str + end)))
		end--;
	if (start > end)
		start = end;
	trimmed = ft_calloc(end - start + 2, sizeof(char));
	if (!(trimmed))
		return (0);
	ft_memcpy(trimmed, str + start, (end - start + 1));
	return (trimmed);
}
