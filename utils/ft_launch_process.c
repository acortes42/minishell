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

static void	ft_execute_absolute_shell_command(t_abs_struct *base,
	char *cmd, t_process *p)
{
	execve(cmd, p->argv, base->env);
	if (errno == EACCES)
		p->status = 126;
	p->completed = 1;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

static void	ft_execute_relative_shell_command(t_abs_struct *base,
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
			if (((statbuf.st_mode & __S_IFMT) == __S_IFDIR) ||
				((statbuf.st_mode & __S_IFMT) == __S_IFREG))
				return (tmp);
		}
		free(tmp);
		path = ft_split_shell_by(&paths, ":");
	}
	return (0);
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
	{
		ft_putstr_fd(*p->argv, STDERR_FILENO);
		ft_putstr_fd(": not found command\n", STDERR_FILENO);
		p->completed = 1;
		p->status = 1;
	}
	else
	{
		stat(path, &statbuf);
		if ((statbuf.st_mode & __S_IFMT) == __S_IFDIR)
		{
			ft_putstr_fd(*p->argv, STDERR_FILENO);
			ft_putstr_fd(": is a directory\n", STDERR_FILENO);
			p->completed = 1;
			p->status = 1;
		}
		else if ((statbuf.st_mode & __S_IFMT) == __S_IFREG)
		{
			if (*path == '/' || !ft_strncmp(path, "\"/", 2))
				ft_execute_absolute_shell_command(base, path, p);
			else
				ft_execute_relative_shell_command(base, p);
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
	if (*current->argv[0] == '/')
		ft_execute_absolute_shell_command(base, current->argv[0], current);
	else if (*current->argv[0] == '.')
		ft_execute_relative_shell_command(base, current);
	else
		ft_execute_shell_command_using_path(base, current);
}
