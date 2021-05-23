/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 19:03:21 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_search_env(char **env, char *key)
{
	int			pos;
	char		**tmp;
	size_t		key_len;

	key_len = ft_strlen(key);
	pos = 0;
	tmp = env;
	while (key_len && tmp && *tmp)
	{
		if (ft_strlen(*tmp) > key_len && !ft_memcmp(*tmp, key, key_len)
			&& *((*tmp) + key_len) == '=')
			return (pos);
		tmp++;
		pos++;
	}
	return (-1);
}

static char	*ft_prepare_export_value(char *value)
{
	char					*tri;
	extern t_abs_struct		g_base;
	t_expand_dollar			d;

	ft_memset(&d, 0, sizeof(t_expand_dollar));
	d.base = &g_base;
	if (ft_isspace(*value))
		tri = ft_strdup("");
	else if (!ft_strncmp(value, "~/", 2))
	{
		ft_expand_tilde(&d);
		tri = ft_strjoin(d.expanded, value + 2);
		free(d.expanded);
	}
	else if (!ft_strcmp(value, "~"))
	{
		ft_expand_tilde(&d);
		d.expanded[ft_strlen(d.expanded) - 1] = 0;
		tri = d.expanded;
	}
	else
		tri = ft_strdup(value);
	if (!tri)
		return (0);
	return (tri);
}

static char	*ft_prepare_export(char *key, char *value)
{
	char					*adj;
	char					*tri;

	if (!key || !value)
		return (0);
	tri = ft_prepare_export_value(value);
	if (!tri)
		return (0);
	adj = ft_calloc(ft_strlen(key) + 1 + ft_strlen(tri) + 1, sizeof(char));
	if (!adj)
	{
		free(tri);
		return (0);
	}
	ft_memcpy(adj, key, ft_strlen(key));
	adj[ft_strlen(key)] = '=';
	ft_memcpy(adj + ft_strlen(key) + 1, tri, ft_strlen(tri));
	free(tri);
	return (adj);
}

int	is_env_valid_argument(char *arg)
{
	if (*arg == '$' && *(arg + 1))
		return (1);
	if (!ft_strlen(arg))
		return (1);
	if (ft_isdigit(*arg))
		return (0);
	while (*arg)
	{
		if (ft_strchr("¡'=?¿!\"$%&/().:,;'\"{}+][*><", *arg))
			return (0);
		arg++;
	}
	return (1);
}

int	ft_setenv(t_abs_struct *base, char *arg)
{
	char	**key_value;
	char	*tri;
	int		key_pos;
	char	*expanded_value;
	int		return_value;

	if (extract_key_value(arg, &key_value, &return_value))
		return (return_value);
	ft_delete_existing_key(base, key_value[0]);
	tri = ft_prepare_export(key_value[0], key_value[1]);
	expanded_value = expand_env_value(base->env, tri);
	key_pos = ft_array_add(&base->env, &base->lines_envp, expanded_value);
	if (!tri || !(key_pos))
	{
		free(expanded_value);
		ft_putstr_fd("\e[0mNo se añadió el argumento\n", STDERR_FILENO);
	}
	ft_array_release(key_value);
	if (tri)
		free(tri);
	return (1);
}
