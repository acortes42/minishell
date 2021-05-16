/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_process_cmd.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:54 by visv              #+#    #+#             */
/*   Updated: 2021/05/16 18:41:09 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	give_char(char d)
{
	if (!d)
		return ('\'');
	return (0);
}

static void	expand_char(t_expand_dollar *d)
{
	if (d->scape)
		ft_expand_scape(d);
	else if (*d->cmd == '\'')
	{
		if (d->single_quote)
			d->single_quote = 0;
		else
			d->single_quote = give_char(d->single_quote);
		if (d->quote)
			*(d->expanded + d->pos++) = *d->cmd;
		d->cmd++;
	}
	else if (*d->cmd == '"' && !d->single_quote && !d->scape)
		ft_expand_quote(d);
	else if (!ft_strncmp("$?", d->cmd, 2) && ((!d->single_quote) || d->quote))
		ft_print_last_process_status(d);
	else if (!ft_strncmp("$", d->cmd, 1) && (!d->single_quote || d->quote))
		ft_expand_dollar(d);
	else if (*d->cmd == '\\' && !d->single_quote)
	{
		d->scape = give_int(d->scape);
		d->cmd++;
	}
	else
	{
		*(d->expanded + d->pos++) = *d->cmd;
		d->cmd++;
	}
}

static void	process_tilde_expansion(t_expand_dollar *d)
{
	if (!ft_strncmp(d->cmd, "~/", 2))
	{
		ft_expand_tilde(d);
		d->cmd += 2;
	}
	else if (!ft_strcmp(d->cmd, "~"))
	{
		ft_expand_tilde(d);
		d->cmd++;
	}
}

static char	*expand(t_abs_struct *base, char *cmd)
{
	t_expand_dollar	d;

	ft_memset(&d, 0, sizeof(t_expand_dollar));
	d.cmd = cmd;
	d.base = base;
	if (!cmd)
		d.expanded_len = 0;
	else
		d.expanded_len = ft_strlen(cmd);
	d.expanded = ft_calloc(d.expanded_len + 2, sizeof(char));
	if (!d.expanded_len || !(d.expanded))
		return (0);
	process_tilde_expansion(&d);
	while (d.cmd && *d.cmd != '\0')
		expand_char(&d);
	*(d.expanded + d.pos) = ' ';
	return (d.expanded);
}

int	ft_expand_process_cmd(t_abs_struct *base, t_process *p)
{
	char			*expanded_slice;
	char			*trimmed;
	char			**to_expand;

	if (!p)
		return (1);
	to_expand = p->argv;
	while (to_expand && *to_expand)
	{
		expanded_slice = expand(base, *to_expand);
		if (!(expanded_slice))
			return (0);
		free(*to_expand);
		trimmed = ft_strtrim(expanded_slice, " \t");
		if (!(trimmed))
		{
			free(expanded_slice);
			return (0);
		}
		free(expanded_slice);
		*to_expand = trimmed;
		to_expand++;
	}
	return (1);
}
