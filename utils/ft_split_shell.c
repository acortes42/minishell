/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:47 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:19:02 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char		*find_next_single_quote(char *ptr)
{
	if (!ptr)
		return (0);
	while (*ptr && *ptr != '\'')
		ptr++;
	return (ptr);
}

static char		*find_next_double_qoute(char *ptr)
{
	int			scape;
	int			single_quote;

	if (!ptr)
		return (0);
	single_quote = 0;
	scape = 0;
	while (*ptr && (*ptr != '"' || scape || single_quote))
	{
		if (*ptr == '\'')
			single_quote = single_quote ? 0 : 1;
		scape = (!scape && *ptr == '\\' ? 1 : 0);
		ptr++;
	}
	return (ptr);
}

char			*ft_split_shell(char **str)
{
	return (ft_split_shell_by(str, ";"));
}

char			*ft_split_shell_by(char **str, char *separator)
{
	char		*ptr;
	char		*splitted;
	size_t		len;

	if (!str || !*str || !(**str))
		return (0);
	ptr = *str;
	while (*ptr && *ptr != '\0' &&
		ft_strncmp(ptr, separator, ft_strlen(separator)))
	{
		if (*ptr == '\'')
			ptr = find_next_single_quote(ptr + 1);
		if (*separator != '"' && *ptr == '"')
			ptr = find_next_double_qoute(ptr + 1);
		ptr++;
	}
	len = ptr - (*str) + 1;
	if (!(splitted = ft_calloc(len, sizeof(char))))
		return (0);
	ft_strlcpy(splitted, *str, len);
	*str = ptr;
	if (!ft_strncmp(*str, separator, ft_strlen(separator)))
		(*str) += ft_strlen(separator);
	return (splitted);
}
