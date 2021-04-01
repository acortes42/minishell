/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_home.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:03:49 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:04:03 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../tests_minishell.h"

char	*ft_build_home(void)
{
	char	*cwd;
	char	*path_sep;
	char	*home;

	cwd = getcwd(0, 0);
	if (!cwd)
		return (0);
	path_sep = strchr(cwd + 1, '/');
	home = calloc(path_sep - cwd + 1, sizeof(char));
	if (home)
		memcpy(home, cwd, path_sep - cwd);
	free(cwd);
	return (home);
}

char	*ft_build_home_slash_ended(void)
{
	char	*cwd;
	char	*path_sep;
	char	*home;

	cwd = getcwd(0, 0);
	if (!cwd)
		return (0);
	path_sep = strchr(cwd + 1, '/');
	home = calloc(path_sep - cwd + 2, sizeof(char));
	if (home)
		memcpy(home, cwd, path_sep - cwd + 1);
	free(cwd);
	return (home);
}
