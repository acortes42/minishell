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

static void			ft_print_last_process_status(t_expand_dollar *d)
{
	char			*expansion;
	char			*status;
	int				len;

	status = ft_itoa(!d->base->last_executed_process ? 0 :
		d->base->last_executed_process->status);
	if (!status)
		ft_exit_minishell(d->base, 1);
	len = ft_strlen(status);
	if (len > 2)
	{
		if (!(expansion = ft_calloc(d->expanded_len + (len - 2) + 1,
			sizeof(char))))
			ft_exit_minishell(d->base, 1);
		ft_memcpy(expansion, d->expanded, d->pos);
		ft_memcpy(expansion + d->pos, status, len);
		d->pos += len;
		free(d->expanded);
		d->expanded = expansion;
		d->expanded_len += (len - 2);
	}
	else
	{
		ft_memcpy(d->expanded + d->pos, status, len);
		d->pos += len;
	}
	d->cmd += 2;
	free(status);
}

static void			expand_char(t_expand_dollar *d)
{
	if (d->scape)
	{
		ft_expand_scape(&d->expanded, &d->cmd, &d->pos);
		d->scape = 0;
		return ;
	}
	else if (*d->cmd == '\'' && !d->quote)
		d->single_quote = (!d->single_quote ? '\'' : 0);
	else if (*d->cmd == '"' && !d->single_quote && !d->scape)
		d->quote = (!d->quote ? '"' : d->quote);
	else if (*d->cmd == '$' && (d->quote || !d->single_quote))
	{
		if (*(d->cmd + 1) == '?')
			ft_print_last_process_status(d);
		else
			ft_expand_dollar(d);
		return ;
	}
	else if (*d->cmd == '\\')
		d->scape = (d->scape ? 0 : 1);
	*(d->expanded + d->pos++) = *d->cmd;
	d->cmd++;
}

static char			*expand(t_abs_struct *base, char *cmd)
{
	t_expand_dollar	d;

	ft_memset(&d, 0, sizeof(t_expand_dollar));
	d.cmd = cmd;
	d.base = base;
	d.expanded_len = (!cmd ? 0 : ft_strlen(cmd));
	if (!d.expanded_len || !(d.expanded = ft_calloc(d.expanded_len + 2,
		sizeof(char))))
		return (0);
	while (d.cmd && *d.cmd != '\0')
	{
		expand_char(&d);
	}
	*(d.expanded + d.pos) = ' ';
	return (d.expanded);
}

int					ft_expand_process_cmd(t_abs_struct *base, t_process *p)
{
	char			*expanded_slice;
	char			*trimmed;
	char			**to_expand;

	if (!p)
		return (1);
	to_expand = p->argv;
	while (to_expand && *to_expand)
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
		ft_remove_quotes(trimmed);
		*to_expand = trimmed;
		to_expand++;
	}
	return (1);
}
