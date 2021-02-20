#include "minishell.h"

static void		ft_execute_absolute_shell_command(abs_struct *base,
	t_process *p)
{
	if (execve(p->argv[0], p->argv, base->env) && errno == EACCES)
		p->status = 126;
	p->completed = 1;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
}

static void		ft_execute_relative_shell_command(abs_struct *base,
	t_process *p)
{
	char		*path;
	char		*tmp;

	if (!(path = getcwd(0, 0)))
		return ;
	tmp = ft_strjoin(path, p->argv[0] + 1);
	free(path);
	path = tmp;
	ft_execute_absolute_shell_command(base, p);
	free(path);
}

static void		ft_execute_shell_command_using_path(abs_struct *base,
	t_process *p)
{
	struct stat	statbuf;
	char		*paths;
	char		*path;
	char		*tmp;
	char		*orig_path;
	
	paths = ft_getenv(base->env, "PATH");
	orig_path = *p->argv;
	paths += 5;
	while ((path = ft_split_shell_by(&paths, ":")))
	{
		tmp = ft_strlcat_paths(path, orig_path);
		*p->argv = tmp;
		free(path);
		if (!stat(*p->argv, &statbuf)/* &&
			(statbuf.st_mode & __S_IFMT) == __S_IFREG*/)  //Aqui comente para hacer prueba
		{
			if (**p->argv == '/' || !ft_strncmp(*p->argv, "\"/", 2))
				ft_execute_absolute_shell_command(base, p);
			else
				ft_execute_relative_shell_command(base, p);
		}
		free(*p->argv);
		*p->argv = orig_path;
	}
	ft_putstr_fd(*p->argv, STDERR_FILENO);
	ft_putstr_fd(": not found command\n", STDERR_FILENO);
	p->completed = 1;
	p->status = 1;
}

static int		prepare_process(abs_struct *base, t_process *p, t_files_fd files_fd)
{
	int			ret;

	if ((ret = set_redirections(base, p)) || (ret = ft_set_default_signals()))
		return (ret);
	if (files_fd.infile != STDIN_FILENO)
	{
		if (dup2(files_fd.infile, STDIN_FILENO) >= 0)
			close(files_fd.infile);
		else
			ft_putstr_fd(strerror(errno), STDERR_FILENO);
	}
	if (files_fd.outfile != STDOUT_FILENO)
	{
		if (dup2(files_fd.outfile, STDOUT_FILENO) >= 0)
			close(files_fd.outfile);
		else
			ft_putstr_fd(strerror(errno), STDERR_FILENO);		
	}
	if (files_fd.errfile != STDERR_FILENO)
	{
		if (dup2(files_fd.errfile, STDERR_FILENO) >= 0)
			close(files_fd.errfile);
		else
			ft_putstr_fd(strerror(errno), STDERR_FILENO);		
	}
	return (errno);
}


void            ft_launch_process(abs_struct *base, t_process *p,
	t_files_fd files_fd)
{
	p->status = prepare_process(base, p, files_fd);
	if (p->status)
		return ;
	if (*p->argv[0] == '/')
		ft_execute_absolute_shell_command(base, p);
	else if (*p->argv[0] == '.')
		ft_execute_relative_shell_command(base, p);
	else
		ft_execute_shell_command_using_path(base, p);
}
