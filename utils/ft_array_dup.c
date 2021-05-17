/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_dup.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:16:58 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 16:02:33 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_array_dup(char **envp)
{
	size_t		l;
	char		**dup;

	dup = NULL;
	if (!envp)
		return (dup);
	l = 0;
	while (*(envp + l))
		l++;
	dup = malloc(sizeof(char *) * (l + 1));
	if (!(dup))
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

char	**ft_array_dup_without(char **env, size_t len_env, char *not_dup)
{
	char	**it_new;
	size_t	i;
	size_t	j;

	it_new = malloc(sizeof(char *) * len_env);
	if (!(it_new))
		ft_exit_minishell(1);
	i = 0;
	j = 0;
	while (env && *(env + i))
	{
		if (*(env + i) != not_dup)
		{
			*(it_new + j) = *(env + i);
			j++;
		}
		i++;
	}
	*(it_new + j) = NULL;
	return (it_new);
}
