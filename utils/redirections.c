#include "minishell.h"

static int	extract_redirections_from_argv(t_process *p)
{
	char	**i;
	char	*tmp;
	char	*argv;
	int		redirs_len;
	int		argv_pos;

	ft_array_release(p->redirs);
	i = p->argv;
	argv_pos = 0;
	redirs_len = 0;
	while (*i)
	{
		argv = *i;
		tmp = 0;
		if ((!(tmp = ft_split_shell_by(&argv, ">")) &&
			!(tmp = ft_split_shell_by(&argv, ">>")) && 
			!(tmp = ft_split_shell_by(&argv, "<"))) ||
			(!argv || *argv == '\0'))
			i++;
		else
		{
			ft_array_add(&p->redirs, &redirs_len,  *i);
			ft_array_slide_left(i);
		}
		if (tmp)
			free(tmp);
	}
	return (1);
}

static void	apply_output_redirection(char *left_side, char *right_side)
{
	(void)left_side;
	(void)right_side;
}

static void	apply_output_add_redirection(char *left_side, char *right_side)
{
	(void)left_side;
	(void)right_side;
}

static void	apply_input_redirection(char *left_side, char *right_side)
{
	(void)left_side;
	(void)right_side;
}

int			set_redirections(t_process *p)
{
	char	**i;
	char	*tmp;	

	if (!p || !p->argv || !extract_redirections_from_argv(p))
		return (0);
	i = p->redirs;
	while (i && *i)
	{
		if ((tmp = ft_split_shell_by(i, ">")))
			apply_output_redirection(tmp, *i);
		else if ((tmp = ft_split_shell_by(i, ">>")))
			apply_output_add_redirection(tmp, *i);
		else if ((tmp = ft_split_shell_by(i, "<")))
			apply_input_redirection(tmp, *i);
		if (tmp)
			free(tmp);
		i++;
	}
	return (1);
}