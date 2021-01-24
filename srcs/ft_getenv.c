/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:04:45 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*ft_getenv(char **env, char *env_key)
{
	char	**tmp;
	size_t	key_len;

	key_len = ft_strlen(env_key);
	tmp = env;
    while (tmp && *tmp)
    {
        if (ft_strlen(*tmp) > key_len && 
			!ft_memcmp(*tmp, env_key, key_len) && *((*tmp) + key_len) == '=')
             return (*tmp);
        tmp++;
    }
    return (NULL);
}
