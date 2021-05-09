/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_launch_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:19 by visv              #+#    #+#             */
/*   Updated: 2021/04/20 14:27:37 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_path_to_execute(char *paths, char *cmd)
{
	struct stat	statbuf;
	char		*path;
	char		*tmp;

	path = ft_split_shell_by(&paths, ":");
	while (path)
	{
		tmp = ft_strlcat_paths(path, cmd);
		free(path);
		if (!stat(tmp, &statbuf))
		{
			if (((statbuf.st_mode & S_IFMT) == S_IFDIR)
				|| ((statbuf.st_mode & S_IFMT) == S_IFREG))
				return (tmp);
		}
		free(tmp);
		path = ft_split_shell_by(&paths, ":");
	}
	return (0);
}

static void	ft_process_not_found_command(t_process *p)
{
	ft_putstr_fd(*p->argv, STDERR_FILENO);
	ft_putstr_fd(": not found command\n", STDERR_FILENO);
	p->completed = 1;
	p->status = 1;
}

static void	ft_process_is_a_directory_command(t_process *p)
{
	ft_putstr_fd(*p->argv, STDERR_FILENO);
	ft_putstr_fd(": is a directory\n", STDERR_FILENO);
	p->completed = 1;
	p->status = 1;
}

static void	ft_execute_shell_command_using_path(t_abs_struct *base,
	t_process *p)
{
	struct stat	statbuf;
	char		*paths;
	char		*path;

	paths = ft_getenv(base->env, "PATH") + 5;
	path = ft_get_path_to_execute(paths, p->argv[0]);
	if (!path)
		ft_process_not_found_command(p);
	else
	{
		stat(path, &statbuf);
		if ((statbuf.st_mode & S_IFMT) == S_IFDIR)
			ft_process_is_a_directory_command(p);
		else if ((statbuf.st_mode & S_IFMT) == S_IFREG)
		{
			ft_execute_absolute_shell_command(base, path, p);
		}
		free(path);
	}
}

void	ft_launch_process(t_abs_struct *base, t_process *current)
{
	current->status = ft_set_default_signals();
	if (current->status)
		return ;
	current->status = set_redirections(base, current);
	if (current->status)
		return ;
	if (*current->argv[0] == '/' || !ft_strncmp(current->argv[0], "./", 2)
		|| !ft_strncmp(current->argv[0], "../", 3))
		ft_execute_absolute_shell_command(base, current->argv[0], current);
	else
		ft_execute_shell_command_using_path(base, current);
}
