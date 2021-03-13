/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:30:48 by vsempere          #+#    #+#             */
/*   Updated: 2019/12/12 14:13:45 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t			ft_strlcat(char *dst, const char *src, size_t size)
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

char			*ft_strlcat_paths(char *prefix, const char *rel_path)
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
	if (!prefix_len)
		add_slash = 0;
	else
		add_slash = (*(prefix + prefix_len - 1) != '/' &&
			ft_strncmp((prefix + prefix_len - 2), "/\"", 2) ? 1 : 0);
	rel_path_len = ft_strlen(rel_path);
	if (!(ret = ft_calloc(prefix_len + add_slash + rel_path_len + 1,
		sizeof(char))))
		return (0);
	ft_strlcpy(ret, prefix, prefix_len + 1);
	if (add_slash)
		*(ret + prefix_len) = '/';
	ft_strlcpy(ret + prefix_len + add_slash, rel_path, rel_path_len + 1);
	return (ret);
}
