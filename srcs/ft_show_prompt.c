/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_show_prompt.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:54:19 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 17:05:15 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_cwd(void)
{
	char		*cwd;

	cwd = getcwd(0, 0);
	if (!cwd || *cwd == '(')
	{
		if (cwd)
			free(cwd);
		ft_exit_minishell(errno);
	}
	return (cwd);
}

int	ft_value_to_len(char *home)
{
	if (!home)
		return (0);
	return (ft_strlen(home));
}

static void	ft_show_prompt_cwd(t_abs_struct *base)
{
	char		*cwd;
	char		*tmp;
	size_t		len;
	char		*home;

	cwd = ft_get_cwd();
	home = ft_getenv(base->env, "HOME");
	if (home)
		home += 5;
	len = ft_value_to_len(home);
	while (len && *(home + len - 1) == '/')
		len--;
	if (len && !ft_strncmp(cwd, home, len))
	{
		tmp = ft_strdup(cwd + len - 1);
		free(cwd);
		if (!tmp)
			ft_exit_minishell(-1);
		cwd = tmp;
		cwd[0] = '~';
	}
	ft_putstr(cwd);
	free(cwd);
}

static void	ft_show_prompt_user(t_abs_struct *base)
{
	char		*str;
	size_t		len;

	str = ft_getenv(base->env, "USER");
	ft_putstr(ANSI_COLOR_GREEN);
	ft_putstr(str + 5);
	str = ft_getenv(base->env, "SESSION_MANAGER");
	if (str)
	{
		ft_putstr("@");
		len = ft_strchr(str, ':') - str - 16;
		ft_putnstr(str + 16, len);
	}
	ft_putstr(ANSI_COLOR_RESET);
}

void	ft_show_prompt(t_abs_struct *base)
{
	ft_show_prompt_user(base);
	ft_putstr(":");
	ft_putstr(ANSI_COLOR_BLUE);
	ft_show_prompt_cwd(base);
	ft_putstr(ANSI_COLOR_RESET);
	ft_putstr("$ ");
}
