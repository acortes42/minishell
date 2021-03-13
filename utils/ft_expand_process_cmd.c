/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_process_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:54 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:17:56 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		ft_expand_scape(char **res, char **cmd, size_t *pos)
{
	*((*res) + *pos) = **cmd;
	(*cmd)++;
	(*pos)++;
	return (1);
}

static char		*ft_extract_variable_name(char **cmd)
{
	char		*tmp;
	char		*ret;

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

static int		ft_expand_dollar(t_expand_dollar *d)
{
	char		*key;
	char		*variable;
	char		*tmp;
	size_t		key_len;
	size_t		variable_len;

	(d->cmd)++;
	key = ft_extract_variable_name(&d->cmd);
	key_len = ft_strlen(key);
	if (key[key_len] == '\n')
		key[key_len--] = '\0';
	if (!key_len) {
		if (key)
			free(key);
		return (1);
	}
	if (!(variable = ft_getenv(d->base->env, key)))
		variable_len = 0;
	else
	{
		variable = variable + key_len + 1;
		variable_len = ft_strlen(variable);	
	}
	if ((variable_len + 1) > key_len)
	{
		d->expanded_len = d->expanded_len + variable_len - key_len - 1 + 1;
		if (!(tmp = ft_calloc(d->expanded_len + 1, sizeof(char))))
		{
			free(key);
			return (0);
		}
		if (d->expanded)
		{
			ft_strlcat(tmp, d->expanded, d->pos + 1);
			free(d->expanded);
		}
		d->expanded = tmp;
	}
	ft_memcpy(d->expanded + d->pos, variable, variable_len);
	d->pos += variable_len;
	free(key);
	return (1);
}

static char			*expand(t_abs_struct *base, char *cmd)
{
	t_expand_dollar	d;
	char			quote;
	char			single_quote;
	int				scape;

	d.cmd = cmd;
	d.base = base;
	d.expanded_len = (!cmd ? 0 : ft_strlen(cmd));
	if (!d.expanded_len || !(d.expanded = ft_calloc(d.expanded_len + 2,
		sizeof(char))))
		return (0);
	d.pos = 0;
	single_quote = 0;
	quote = 0;
	scape = 0;
	while (d.cmd && *d.cmd != '\0')
	{
		if (scape)
		{
			if (!ft_expand_scape(&d.expanded, &d.cmd, &d.pos))
			{
				free(d.expanded);
				return (0);
			}
			scape = 0;
			continue ;
		}
		else if (*d.cmd == '\'' && !quote)
		{
			single_quote = (!single_quote ? '\'' : 0);
			*(d.expanded + d.pos++) = *d.cmd;
		}
		else if (*d.cmd == '"' && !single_quote && !scape)
		{
			quote = (!quote ? '"' : quote);
			*(d.expanded + d.pos++) = *d.cmd;
		}
		else if (*d.cmd == '$' && (quote || !single_quote))
		{
			ft_expand_dollar(&d);
			continue ;
		}
		else if (*d.cmd == '\\')
		{
			scape = (scape ? 0 : 1);
			*(d.expanded + d.pos++) = *d.cmd;
		}
		else
			*(d.expanded + d.pos++) = *d.cmd;
		d.cmd++;
	}
	*(d.expanded + d.pos) = ' ';
	return (d.expanded);
}

static void		remove_quotes(char *field)
{
	size_t		len;
	size_t		pos;

	len = ft_strlen(field);
	if (!len)
		return ;
	if ((*field != '"' || *(field + len - 1) != '"') &&
		(*field != '\'' || *(field + len - 1) != '\''))
		return ;
	pos = 1;
	while (*(field + pos) && pos < (len - 1))
	{
		*(field + pos - 1) = *(field + pos);
		pos++;
	}
	*(field + pos - 1) = *(field + len);
}

int				ft_expand_process_cmd(t_abs_struct *base, t_process *p)
{
	char		*expanded_slice;
	char		*trimmed;
	char		**to_expand;

	if (!p)
		return (1);
	to_expand = p->argv;
	while (*to_expand)
	{
		if (!(expanded_slice = expand(base, *to_expand)))
			return (0);
		free(*to_expand);
		if (!(trimmed = ft_trim(expanded_slice)))
		{
			free(expanded_slice);
			return (0);
		}
		free(expanded_slice);
		remove_quotes(trimmed);
		*to_expand = trimmed;
		to_expand++;
	}
	return (1);
}
