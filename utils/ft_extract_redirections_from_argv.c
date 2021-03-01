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

int			ft_extract_redirections_from_argv(t_process *p)
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
