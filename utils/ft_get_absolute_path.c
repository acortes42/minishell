/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_absolute_path.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 16:05:59 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 14:33:14 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*prepend_to_path(char *prefix, char *path)
{
	char		*new_path;
	size_t		len_prefix;
	size_t		len_path;

	len_prefix = ft_strlen(prefix);
	if (len_prefix && prefix[len_prefix - 1] != '/')
		len_prefix++;
	len_path = ft_strlen(path);
	new_path = ft_calloc((len_prefix + len_path + 1), sizeof(char));
	if (!(new_path))
		return (0);
	*new_path = 0;
	ft_strlcat(new_path, prefix, len_prefix + 1);
	if (len_prefix && prefix[len_prefix - 1] != '/')
		new_path[len_prefix - 1] = '/';
	new_path[len_prefix] = 0;
	ft_strlcat(new_path + len_prefix, path, len_path + 1);
	return (new_path);
}

static char	*prepend_home_to_path(t_abs_struct *base, char *path)
{
	char		*home;

	home = ft_getenv(base->env, "HOME");
	if (!home)
		return (ft_strdup(path));
	else
		return (prepend_to_path(home + 5, path));
}

static char	*prepend_pwd_to_path(char *path)
{
	char		*cwd;
	char		*adjusted_path;

	cwd = getcwd(0, 0);
	if (!cwd)
		return (ft_strdup(path));
	else
	{
		adjusted_path = prepend_to_path(cwd, path);
		free(cwd);
		return (adjusted_path);
	}
}

char	*ft_get_absolute_path(t_abs_struct *base, char *path)
{
	int	aux;

	aux = 0;
	if (!path)
		return (0);
	if (*path == '~')
		return (prepend_home_to_path(base, path + 1));
	else if (*path == '/')
		return (ft_strdup(path));
	else
	{
		if (!ft_memcmp(path, "./", 2))
			aux = 2;
		return (prepend_pwd_to_path(path + aux));
	}
}
