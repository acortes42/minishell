/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:40 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:54:10 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_pwd(void)
{
	extern t_abs_struct	g_base;
	char				*cwd;

	cwd = getcwd(0, 0);
	if (!cwd)
	{
		cwd = ft_getenv(g_base.env, "PWD");
		if (cwd)
			cwd = ft_strdup(cwd + 4);
	}
	if (!cwd)
		ft_putstr_fd("getcwd() error", STDERR_FILENO);
	else
	{
		ft_putstr(cwd);
		ft_putstr("\n");
		free(cwd);
	}
	return (1);
}

int	ft_help(void)
{
	ft_putstr("\e[0mLos comandos disponibles són los siguientes:\n\n");
	ft_putstr("exit\necho\npwd\ncd\nhelp\nenv\nunset\n");
	ft_putstr("clear\nexport\n");
	return (1);
}
