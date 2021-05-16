/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extract_redirections_from_argv.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:57 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 14:34:56 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	contains_redir(char *str)
{
	return (str && (ft_strchr(str, '>') || ft_strchr(str, '<')));
}

int	complete_redir_with_next_argv(char *str)
{
	int		len;

	len = ft_strlen(str);
	if (len && (*(str + len - 1) == '>' || *(str + len - 1) == '<'))
		return (1);
	else
		return (0);
}

static void	add_redir_joining_adjacent_params(char ***redirs, int *redirs_len,
	char **params)
{
	char	*redir;

	redir = ft_strjoin(*params, *(params + 1));
	ft_array_add(redirs, redirs_len, redir);
	free(*params);
	ft_array_slide_left(params);
	free(*params);
}

int	ft_extract_redirections_from_argv(t_process *p)
{
	char	**i;
	int		redirs_len;

	if (!p || !p->argv)
		return (0);
	i = p->argv + 1;
	redirs_len = 0;
	while (*i)
	{
		if (!contains_redir(*i))
			i++;
		else
		{
			if (complete_redir_with_next_argv(*i) && *(i + 1))
				add_redir_joining_adjacent_params(&p->redirs, &redirs_len, i);
			else
				ft_array_add(&p->redirs, &redirs_len, *i);
			ft_array_slide_left(i);
		}
	}
	return (1);
}
