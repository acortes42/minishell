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
	int		redir;
	char	*tmp;
	char	*argv;

	argv = str;
	tmp = ft_split_shell_by(&argv, ">");
	redir = 0;
	if (tmp && *(argv - 1) == '>')
		redir = 1;
	if (tmp)
		free(tmp);
	if (redir)
		return (redir);
	argv = str;
	tmp = ft_split_shell_by(&argv, "<");
	redir = 0;
	if (tmp && *(argv - 1) == '<')
		redir = 1;
	if (tmp)
		free(tmp);
	return (redir);
}

int	ft_extract_redirections_from_argv(t_process *p)
{
	char	**i;
	int		redirs_len;

	i = p->argv;
	redirs_len = 0;
	while (*i)
	{
		if (!contains_redir(*i))
			i++;
		else
		{
			ft_array_add(&p->redirs, &redirs_len, *i);
			ft_array_slide_left(i);
		}
	}
	return (1);
}
