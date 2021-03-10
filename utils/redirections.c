#include "minishell.h"

static int	apply_output_redirection(abs_struct *base, char *fd,
	char *right_side)
{
	int		i_fd;
	int		o_fd;
	int		empty;
	char	*fd_file;

	empty = 0;
	if (!ft_isinteger(fd) && !(empty = ft_isempty(fd)))
		return (0);
	i_fd = empty ? STDOUT_FILENO : ft_atoi(fd);
	if (!(fd_file = ft_trim(right_side)))
		return (1);
	if (!ft_strncmp(fd_file, "&-", 2))
	{
		free(fd_file);
		// TODO: Comprobar si el fd está abierto como salida, sino dar error (stat)
		return (close(i_fd));
	}
	if ((o_fd = open((fd_file + (*fd_file == '&' ? 1 : 0)),
		O_CREAT | O_TRUNC | O_WRONLY, 0666)) < 0)
		ft_exit_minishell(base, errno);
	if (dup2(o_fd, i_fd) < 0)
		ft_exit_minishell(base, errno);	
	if (*fd_file != '&')
		close(o_fd);
	free(fd_file);
	return (0);
}

static int	apply_output_add_redirection(abs_struct *base, char *fd,
	char *right_side)
{
	int		i_fd;
	int		o_fd;
	int		empty;
	char	*fd_file;

	empty = 0;
	if (!ft_isinteger(fd) && !(empty = ft_isempty(fd)))
		return (0);
	i_fd = empty ? STDOUT_FILENO : ft_atoi(fd);
	if (!(fd_file = ft_trim(right_side)))
		return (1);
	if (!ft_strncmp(fd_file, "&-", 2))
	{
		free(fd_file);
		// TODO: Comprobar si el fd está abierto como entrada, sino dar error (stat)
		return (close(i_fd));
	}
	if ((o_fd = open((fd_file + (*fd_file == '&' ? 1 : 0)),
		O_APPEND | O_RDWR | O_CREAT, 0666)) < 0)
		ft_exit_minishell(base, errno);
	if (dup2(o_fd, i_fd) < 0)
		ft_exit_minishell(base, errno);	
	if (*fd_file != '&')
		close(o_fd);
	free(fd_file);
	return (0);
}

static int	apply_input_redirection(abs_struct *base, char *fd, char *right_side)
{
	int		i_fd;
	int		o_fd;
	int		empty;
	char	*fd_file;

	empty = 0;
	if (!ft_isinteger(fd) && !(empty = ft_isempty(fd)))
		return (0);
	i_fd = empty ? STDIN_FILENO : ft_atoi(fd);
	if (!(fd_file = ft_trim(right_side)))
		return (1);
	if (!ft_strncmp(fd_file, "&-", 2))
	{
		free(fd_file);
		// TODO: Comprobar si el fd está abierto como entrada, sino dar error (stat)
		return (close(i_fd));
	}
	if ((o_fd = open((fd_file + (*fd_file == '&' ? 1 : 0)), O_RDONLY)) < 0)
		ft_exit_minishell(base, errno);
	if (dup2(o_fd, i_fd) < 0)
		ft_exit_minishell(base, errno);	
	if (*fd_file != '&')
		close(o_fd);
	free(fd_file);
	return (0);
}

static int	set_redirection(abs_struct *base, char *i)
{
	char	*redir;
	char	*fd;
	int		redirected;

	fd = 0;
	redirected = 0;
	if ((redir = i) && (fd = ft_split_shell_by(&redir, ">>")) &&
		*(redir - 1) == '>')
		redirected = apply_output_add_redirection(base, fd, redir);
	if (fd)
		free(fd);
	if (*(redir - 1) == '>' && !redirected)
		return (0);
	fd = 0;
	if (!redirected && (redir = i) &&
		(fd = ft_split_shell_by(&redir, ">")) && *(redir - 1) == '>')
		redirected = apply_output_redirection(base, fd, redir);
	if (fd)
		free(fd);
	if (*(redir - 1) == '>' && !redirected)
		return (0);
	fd = 0;
	if (!redirected && (redir = i) &&
		(fd = ft_split_shell_by(&redir, "<")) && *(redir - 1) == '<')
		redirected = apply_input_redirection(base, fd, redir);
	if (fd)
		free(fd);
	return (redirected);
}

int			set_redirections(abs_struct *base, t_process *p)
{
	char	**i;
	int		redirected;

	if (!p || !p->argv || !ft_extract_redirections_from_argv(p))
		return (1);
	i = p->redirs;
	redirected = 0;
	while (!redirected && i && *i)
	{
		if ((redirected = set_redirection(base, *i)))
			return (redirected);
		i++;
	}
	return (redirected);
}