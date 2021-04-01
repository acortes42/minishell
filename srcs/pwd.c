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
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
	{
		ft_putstr(cwd);
		ft_putstr("\n");
	}
	else
		ft_putstr_fd("getcwd() error", STDERR_FILENO);
	return (1);
}

int	ft_help(void)
{
	ft_putstr("\e[0mLos comandos disponibles són los siguientes:\n\n");
	ft_putstr("exit\necho\npwd\ncd\nhistory\nhelp\nenv\nunset\n");
	ft_putstr("clear\nexport\n");
	return (1);
}
