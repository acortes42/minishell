/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_process_cmd_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:02:24 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 15:00:58 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	give_int(int d)
{
	if (d)
		return (0);
	return (1);
}

int	ft_expand_scape(char **res, char **cmd, size_t *pos)
{
	*((*res) + *pos) = **cmd;
	(*cmd)++;
	(*pos)++;
	return (1);
}

char	*ft_extract_variable_name(char **cmd)
{
	char	*tmp;
	char	*ret;

	if (!cmd || !(*cmd))
		return (0);
	tmp = *cmd;
	while (*cmd && !ft_isspace(**cmd) && **cmd != '"' && **cmd != '\'' \
				 && **cmd != '$' && (**cmd))
		(*cmd)++;
	ret = ft_calloc(*cmd - tmp + 1, sizeof(char));
	if (!(ret))
		return (0);
	ft_memcpy(ret, tmp, *cmd - tmp);
	return (ret);
}

static char	*ft_getenv_value(char **env, char *key, size_t *key_len)
{
	char	*variable;

	if (key[*key_len] == '\n')
		key[(*key_len)--] = '\0';
	if (!*key_len)
	{
		if (key)
			free(key);
		return (0);
	}
	variable = ft_getenv(env, key);
	if (variable)
		variable = variable + (*key_len) + 1;
	free(key);
	return (variable);
}

int	ft_expand_dollar(t_expand_dollar *d)
{
	t_expand_dollar_internal	i;

	(d->cmd)++;
	i.key = ft_extract_variable_name(&d->cmd);
	i.key_len = ft_strlen(i.key);
	i.variable = ft_getenv_value(d->base->env, i.key, &i.key_len);
	if (!i.variable && !i.key_len)
		i.variable = "$";
	i.variable_len = ft_strlen(i.variable);
	if (i.variable && *(i.variable) != '$' && (i.variable_len + 1) > i.key_len)
	{
		d->expanded_len = d->expanded_len + i.variable_len - i.key_len - 1 + 1;
		ft_calloc(d->expanded_len + 1, sizeof(char));
		if (!(i.tmp))
			return (0);
		if (d->expanded)
		{
			ft_strlcat(i.tmp, d->expanded, d->pos + 1);
			free(d->expanded);
		}
		d->expanded = i.tmp;
	}
	ft_memcpy(d->expanded + d->pos, i.variable, i.variable_len);
	d->pos += i.variable_len;
	return (1);
}
