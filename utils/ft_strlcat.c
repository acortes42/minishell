/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:30:48 by vsempere          #+#    #+#             */
/*   Updated: 2021/04/01 12:17:20 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		i;
	size_t		j;

	i = ft_strnlen(dst, size);
	j = 0;
	if (size)
	{
		while (src[j] && i < (size - 1))
		{
			dst[i] = src[j];
			i++;
			j++;
		}
		if (i < size)
			dst[i] = '\0';
	}
	i += ft_strlen(&src[j]);
	return (i);
}

char	*ft_strlcat_paths(char *prefix, const char *rel_path)
{
	size_t		prefix_len;
	size_t		rel_path_len;
	int			add_slash;
	char		*ret;

	if (!prefix)
		return (ft_strdup(rel_path));
	else if (!rel_path)
		return (ft_strdup(prefix));
	prefix_len = ft_strlen(prefix);
	add_slash = 0;
	if (*(prefix + prefix_len - 1) != '/' && \
		*(prefix + prefix_len - 1) != '\\')
		add_slash = 1;
	rel_path_len = ft_strlen(rel_path);
	ret = ft_calloc(prefix_len + add_slash + rel_path_len + 1, sizeof(char));
	if (!(ret))
		return (0);
	ft_strlcpy(ret, prefix, prefix_len + 1);
	if (add_slash)
		*(ret + prefix_len) = '/';
	ft_strlcpy(ret + prefix_len + add_slash, rel_path, rel_path_len + 1);
	return (ret);
}
