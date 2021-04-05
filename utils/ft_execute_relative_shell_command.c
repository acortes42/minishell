/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:19 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 14:18:50 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execute_relative_shell_command(t_abs_struct *base,
	t_process *p)
{
	char		*path;
	char		*tmp;

	path = getcwd(0, 0);
	if (!(path))
		return ;
	tmp = ft_strjoin(path, p->argv[0] + 1);
	free(path);
	path = tmp;
	ft_execute_absolute_shell_command(base, path, p);
	free(path);
}
