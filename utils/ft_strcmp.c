/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 12:24:33 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/08 12:25:32 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	int i;

	i = 0;
	if (s1[i] == '\0' || s1[i] != s2[i])
		return ((unsigned char)s1[i] - s2[i]);
	i++;
	return ((unsigned char)s1[i] - s2[i]);
}
