#include "minishell.h"

static int	contains_redir(char *str)
{
	int		redir;
	char	*tmp;
	char	*argv;

	argv = str;
	tmp = 0;
	redir = (((tmp = ft_split_shell_by(&argv, ">")) &&
		*(argv - 1) == '>') ? 1 : 0);
	if (tmp)
		free(tmp);
	if (redir)
		return (redir);
	argv = str;
	redir = (((tmp = ft_split_shell_by(&argv, "<")) &&
		*(argv - 1) == '<') ? 1 : 0);
	if (tmp)
		free(tmp);
	return (redir);
}

static int	extract_redirections_from_argv(t_process *p)
{
	char	**i;
	int		redirs_len;

	i = p->argv;
	redirs_len = 0;
	while (*i)
	{
		if (!contains_redir(*i))
			i++;
		else
		{
			ft_array_add(&p->redirs, &redirs_len,  *i);
			ft_array_slide_left(i);
		}
	}
	return (1);
}

static int	apply_output_redirection(abs_struct *base, char *fd, char *right_side, t_process *p)
{
	int		i_fd;
	int		o_fd;
	int		empty;
	char	*abs_path;

	empty = 0;
	if (!ft_isinteger(fd) && !(empty = ft_isempty(fd)))
		return (0);
	i_fd = empty ? STDOUT_FILENO : ft_atoi(fd);
	if (!ft_strncmp(right_side, "&-", 2))
	{
		// TODO: Comprobar si el fd está abierto como salida, sino dar error (stat)
		return (close(i_fd));
	}
	if (i_fd == STDOUT_FILENO)
		p->std_fds.outfile = dup(STDOUT_FILENO);
	if (!(abs_path = ft_get_absolute_path(base, right_side)))
		return (1);
	if ((o_fd = open(abs_path, O_CREAT | O_TRUNC | O_WRONLY, 0666)) < 0 ||
		dup2(o_fd, i_fd) < 0)
	{
		free(abs_path);
		if (o_fd > -1)
			close(o_fd);
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		return (errno);
	}
	free(abs_path);
	if (*right_side != '&')
		close(o_fd);
	return (0);
}

static int	apply_output_add_redirection(char *fd, char *right_side)
{
	(void)fd;
	(void)right_side;
	
	return (0);
}

static int	apply_input_redirection(char *fd, char *right_side)
{
	(void)fd;
	(void)right_side;
	
	return (0);
}

int			set_redirections(abs_struct *base, t_process *p)
{
	char	**i;
	char	*fd;
	char	*redir;
	int		redirected;

	if (!p || !p->argv || !extract_redirections_from_argv(p))
		return (1);
	i = p->redirs;
	fd = 0;
	redirected = 0;
	while (!redirected && i && *i)
	{
		if ((redir = *i) && (fd = ft_split_shell_by(&redir, ">>")) &&
			*(redir - 1) == '>')
			redirected = apply_output_add_redirection(fd, redir);
		if (fd)
			free(fd);
		fd = 0;
		if (!redirected && (redir = *i) &&
			(fd = ft_split_shell_by(&redir, ">")) && *(redir - 1) == '>')
			redirected = apply_output_redirection(base, fd, redir, p);
		if (fd)
			free(fd);
		fd = 0;
		if (!redirected && (redir = *i) &&
			(fd = ft_split_shell_by(&redir, "<")) && *(redir - 1) == '<')
			redirected = apply_input_redirection(fd, redir);
		if (fd)
			free(fd);
		i++;
	}
	return (redirected);
}