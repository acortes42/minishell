/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_shell_process.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:47 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 14:07:27 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_next_single_quote(char *ptr)
{
	if (!ptr)
		return (0);
	while (*ptr && *ptr != '\'')
		ptr++;
	return (ptr);
}

static char	*find_next_double_qoute(char *ptr)
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
		{
			if (single_quote)
				single_quote = 0;
			else
				single_quote = 1;
		}
		if (!scape && *ptr == '\\')
			scape = 1;
		else
			scape = 0;
		ptr++;
	}
	return (ptr);
}

static char	*ft_extract_split(char **str, char *ptr, char *separator)
{
	char	*splitted;
	size_t	len;

	len = ptr - (*str) + 1;
	splitted = ft_calloc(len, sizeof(char));
	if (!(splitted))
		return (0);
	ft_strlcpy(splitted, *str, len);
	*str = ptr;
	if (**str == *separator && *separator == ' ')
		(*str) += 1;
	return (splitted);
}

char	*ft_split_shell_process(char **str)
{
	char		*ptr;
	char		*chars;

	if (!str || !*str || !(**str))
		return (0);
	chars = " <>";
	ptr = *str;
	if (*ptr == '<')
		ptr++;
	else if (*ptr == '>')
	{
		while (*ptr == '>')
			ptr++;
	}
	while (*ptr && *ptr != '\0' && !ft_strchr(chars, *ptr))
	{
		if (*ptr == '\'')
			ptr = find_next_single_quote(ptr + 1);
		if (*ptr == '"')
			ptr = find_next_double_qoute(ptr + 1);
		if (*ptr)
			ptr++;
	}
	return (ft_extract_split(str, ptr, ptr));
}
