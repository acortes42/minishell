/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isempty.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:05 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 14:32:20 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isempty(const char *s)
{
	const char	*t;

	if (!s)
		return (1);
	t = s;
	while (t && *t != '\0')
	{
		if (!ft_isspace((int)*t))
			return (0);
		t++;
	}
	return (1);
}
