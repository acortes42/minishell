/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:16:58 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:17:04 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**ft_array_dup(char **envp)
{
	size_t		l;
	char		**dup;

	dup = NULL;
	if (!envp)
		return (dup);
	l = 0;
	while (*(envp + l))
		l++;
	if (!(dup = malloc(sizeof(char *) * (l + 1))))
		return (NULL);
	l = 0;
	while (*(envp + l))
	{
		*(dup + l) = ft_strdup(*(envp + l));
		l++;
	}
	*(dup + l) = NULL;
	return (dup);
}
