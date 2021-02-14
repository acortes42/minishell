#include "minishell.h"

static void		ft_execute_absolute_shell_command(abs_struct *base,
	t_process *p)
{
// todo: pendiente de ver si se llama bien
	if (execve(p->argv[0], p->argv, base->env) && errno == EACCES)
	{
		p->status = 126;
	}
	p->completed = 1;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
}

static void		ft_execute_relative_shell_command(abs_struct *base,
	t_process *p)
{
	char		*path;
	char		*tmp;

	//	 todo: Tratar el error de path
	if (!(path = getcwd(0, 0)))
		return ;
	tmp = ft_strjoin(path, p->argv[0] + 1);
	free(path);
	path = tmp;
	// TODO: pendiente de ver si se está llamando bien
	if (execve(path, p->argv + 1, base->env) && errno == EACCES)
	{
		p->status = 126;
	}
	free(path);
	p->completed = 1;
	ft_putstr_fd(strerror(errno), STDERR_FILENO);
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
	while ((path = ft_split_shell_by(&paths, ':')))
	{
		tmp = ft_strlcat_paths(path, orig_path);
		*p->argv = tmp;
		free(path);
		if (!stat(*p->argv, &statbuf) &&
			(statbuf.st_mode & __S_IFMT) == __S_IFREG)
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

static void		prepare_process(t_files_fd files_fd)
{
	/* Set the handling for job control signals back to the default.  */
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	signal(SIGTSTP, SIG_DFL);
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);
	signal(SIGCHLD, SIG_DFL);
	/* Set the standard input/output channels of the new process.  */
	if (files_fd.infile != STDIN_FILENO)
	{
		dup2(files_fd.infile, STDIN_FILENO);
		close(files_fd.infile);
	}
	if (files_fd.outfile != STDOUT_FILENO)
	{
		dup2(files_fd.outfile, STDOUT_FILENO);
		close(files_fd.outfile);
	}
	if (files_fd.errfile != STDERR_FILENO)
	{
		dup2(files_fd.errfile, STDERR_FILENO);
		close(files_fd.errfile);
	}
}

void            ft_launch_process(abs_struct *base, t_process *p,
	t_files_fd files_fd)
{
	prepare_process(files_fd);
	if (ft_execute_builtin(base, p))
	{
		p->completed = 1;
		p->status = 0;
	}
	else if (*p->argv[0] == '/')
		ft_execute_absolute_shell_command(base, p);
	else if (*p->argv[0] == '.')
		ft_execute_relative_shell_command(base, p);
	else
		ft_execute_shell_command_using_path(base, p);
}