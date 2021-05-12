/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 22:15:50 by visv              #+#    #+#             */
/*   Updated: 2021/03/31 12:06:17 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_redirection(t_abs_struct *base, char *i)
{
	int		redirected;

	redirected = 0;
	if (ft_output_add_redirection(base, i, &redirected))
		return (redirected);
	if (ft_output_redirection(i, &redirected))
		return (redirected);
	if (ft_input_redirection(i, &redirected))
		return (redirected);
	return (0);
}

int	set_redirections(t_abs_struct *base, t_process *p)
{
	char	**i;
	int		redirected;

	if (!p || !p->argv || !ft_extract_redirections_from_argv(p))
		return (1);
	i = p->redirs;
	redirected = 0;
	while (i && *i)
	{
		if (set_redirection(base, *i))
			redirected = 1;
		i++;
	}
	return (redirected);
}
