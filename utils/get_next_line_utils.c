/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 21:45:34 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/30 19:58:13 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strcdup(const char *s1, int c)
{
	int		i;
	char	*str;

	i = 0;
	while (s1[i] != c && s1[i] != '\0')
		i++;
	str = malloc(sizeof(char) * (i + 1));
	str[i] = '\0';
	if (str == NULL)
		return (NULL);
	while (i-- > 0)
		str[i] = s1[i];
	return (str);
}
