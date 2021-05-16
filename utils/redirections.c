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

static int	set_redirection(t_abs_struct *base, char *i, int files_must_exist)
{
	int		redirected;
	int		found_redirection;

	found_redirection = 0;
	redirected = 0;
	if (ft_output_add_redirection(base, i, &redirected, files_must_exist))
		found_redirection = 1;
	if (!found_redirection && ft_output_redirection(i, &redirected,
		files_must_exist))
		found_redirection = 1;
	if (!found_redirection && ft_input_redirection(i, &redirected, files_must_exist))
		found_redirection = 1;
	if (found_redirection)
	{
		if (redirected)
			return (redirected);
		else
			return (-1);
	}
	return (0);
}

int	set_redirections(t_abs_struct *base, t_process *p, int files_must_exist)
{
	char	**i;
	int		redirected;
	int		redirOk;

	if (!p || !p->argv || !ft_extract_redirections_from_argv(p))
		return (1);
	i = p->redirs;
	redirected = 0;
	while (i && *i)
	{
		redirOk = set_redirection(base, *i, files_must_exist);
		if (redirOk < 0)
		{
			ft_putstr("Error en la redirección\n");
			return (-1);
		}
		else if (redirOk > 0)
			redirected = 1;
		i++;
	}
	return (redirected);
}
