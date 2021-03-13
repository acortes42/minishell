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

static int		ft_expand_scape(char **res, char **cmd, size_t *pos,
	char single_quote, char quote)
{
	(void)single_quote;
	(void)quote;
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

static int		ft_expand_dollar(t_abs_struct *base, char **expanded,
	size_t *expanded_len, size_t *pos, char **cmd)
{
	char		*key;
	char		*variable;
	char		*tmp;
	size_t		key_len;
	size_t		variable_len;

	(*cmd)++;
	key = ft_extract_variable_name(cmd);
	key_len = ft_strlen(key);
	if (key[key_len] == '\n')
		key[key_len--] = '\0';
	if (!key_len) {
		if (key)
			free(key);
		return (1);
	}
	if (!(variable = ft_getenv(base->env, key)))
		variable_len = 0;
	else
	{
		variable = variable + key_len + 1;
		variable_len = ft_strlen(variable);	
	}
	if ((variable_len + 1) > key_len)
	{
		*expanded_len = *expanded_len + variable_len - key_len - 1 + 1;
		if (!(tmp = ft_calloc(*expanded_len + 1,
			sizeof(char))))
		{
			free(key);
			return (0);
		}
		if (*expanded)
		{
			ft_strlcat(tmp, *expanded, *pos + 1);
			free(*expanded);
		}
		*expanded = tmp;
	}
	ft_memcpy(*expanded + *pos, variable, variable_len);
	*pos += variable_len;
	free(key);
	return (1);
}

static char		*expand(t_abs_struct *base, char *cmd)
{
	char		*res;
	size_t		len;
	size_t		pos;
	char		quote;
	char		single_quote;
	int			scape;

	len = (!cmd ? 0 : ft_strlen(cmd));
	if (!len || !(res = ft_calloc(len + 2, sizeof(char))))
		return (0);
	pos = 0;
	single_quote = 0;
	quote = 0;
	scape = 0;
	while (cmd && *cmd != '\0')
	{
		if (scape)
		{
			if (!ft_expand_scape(&res, &cmd, &pos, single_quote, quote))
			{
				free(res);
				return (0);
			}
			scape = 0;
			continue ;
		}
		else if (*cmd == '\'' && !quote)
		{
			single_quote = (!single_quote ? '\'' : 0);
			*(res + pos++) = *cmd;
		}
		else if (*cmd == '"' && !single_quote && !scape)
		{
			quote = (!quote ? '"' : quote);
			*(res + pos++) = *cmd;
		}
		else if (*cmd == '$' && (quote || !single_quote))
		{
			ft_expand_dollar(base, &res, &len, &pos, &cmd);
			continue ;
		}
		else if (*cmd == '\\')
		{
			scape = (scape ? 0 : 1);
			*(res + pos++) = *cmd;
		}
		else
			*(res + pos++) = *cmd;
		cmd++;
	}
	*(res + pos) = ' ';
	return (res);
}

static void			remove_quotes(char *field)
{
	size_t			len;
	size_t			pos;

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
