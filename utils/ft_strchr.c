/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:29:39 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:29:43 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strchr(const char *s, int c)
{
	c = (char)c;
	while (*s)
	{
		if (*s == c)
			break ;
		else
			s++;
	}
	if (*s == c)
		return ((char *)s);
	return (0);
}

char	*ft_strstr(const char *s, char *tgt)
{
	char	*tgt_it;

	if (!tgt || !s)
		return (0);
	tgt_it = tgt;
	while (*s && *tgt_it)
	{
		if (*s == *tgt_it)
			tgt_it++;
		else
			tgt_it = tgt;
		s++;
	}
	if (!(*tgt_it))
		return ((char *)s);
	return (0);
}
