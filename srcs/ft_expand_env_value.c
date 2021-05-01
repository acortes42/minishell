/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_env_value.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:58:03 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/01 16:58:04 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_home_value(char *home_env)
{
	if (home_env)
		home_env += 5;
	return (home_env);
}

char	*expand_env_value(char **envp, char *env_value)
{
	char		*z[3];
	size_t		offset;

	if (!env_value)
		return (0);
	z[0] = ft_strchr(env_value, '=');
	if (!z[0]++)
		return (0);
	z[1] = 0;
	if (!ft_memcmp(z[0], "~/", 2))
		z[1] = ft_get_home_value(ft_getenv(envp, "HOME"));
	z[2] = malloc(sizeof(char) * ((z[0] - env_value) \
		 + ft_strlen(z[1]) + ft_strlen(z[0]) + ft_check_home((z[1]))));
	if (!(z[2]))
		return (0);
	ft_memcpy(z[2], env_value, z[0] - env_value);
	if (z[1])
		ft_memcpy((z[2] + (z[0] - env_value)), z[1], ft_strlen(z[1]));
	offset = z[0] - env_value + ft_strlen(z[1]);
	if (z[1])
		ft_memcpy(z[2] + offset, z[0] + 1, ft_strlen(z[0]) + -1);
	else
		ft_memcpy(z[2] + offset, z[0] + 0, ft_strlen(z[0]) + 0);
	*(z[2] + offset + ft_strlen(z[0]) + ft_check_home2(z[1])) = 0;
	return (z[2]);
}
