/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_process_cmd_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:02:24 by visv              #+#    #+#             */
/*   Updated: 2021/03/14 09:02:26 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int								ft_expand_scape(char **res, char **cmd,
	size_t *pos)
{
	*((*res) + *pos) = **cmd;
	(*cmd)++;
	(*pos)++;
	return (1);
}

char							*ft_extract_variable_name(char **cmd)
{
	char						*tmp;
	char						*ret;

	if (!cmd || !(*cmd))
		return (0);
	tmp = *cmd;
	while (*cmd && !ft_isspace(**cmd) && **cmd != '"' && **cmd != '\'' &&
		**cmd != '$' && (**cmd))
		(*cmd)++;
	if (!(ret = ft_calloc(*cmd - tmp + 1, sizeof(char))))
		return (0);
	ft_memcpy(ret, tmp, *cmd - tmp);
	return (ret);
}

static char						*ft_getenv_value(char **env, char *key,
	size_t *key_len)
{
	char						*variable;

	if (key[*key_len] == '\n')
		key[(*key_len)--] = '\0';
	if (!*key_len)
	{
		if (key)
			free(key);
		return (0);
	}
	if ((variable = ft_getenv(env, key)))
		variable = variable + (*key_len) + 1;
	free(key);
	return (variable);
}

int								ft_expand_dollar(t_expand_dollar *d)
{
	t_expand_dollar_internal	internal;

	(d->cmd)++;
	internal.key = ft_extract_variable_name(&d->cmd);
	internal.key_len = ft_strlen(internal.key);
	internal.variable = ft_getenv_value(d->base->env, internal.key,
		&internal.key_len);
	if (!internal.variable)
		return (1);
	internal.variable_len = ft_strlen(internal.variable);
	if ((internal.variable_len + 1) > internal.key_len)
	{
		d->expanded_len = d->expanded_len + internal.variable_len
			- internal.key_len - 1 + 1;
		if (!(internal.tmp = ft_calloc(d->expanded_len + 1, sizeof(char))))
			return (0);
		if (d->expanded)
		{
			ft_strlcat(internal.tmp, d->expanded, d->pos + 1);
			free(d->expanded);
		}
		d->expanded = internal.tmp;
	}
	ft_memcpy(d->expanded + d->pos, internal.variable, internal.variable_len);
	d->pos += internal.variable_len;
	return (1);
}
