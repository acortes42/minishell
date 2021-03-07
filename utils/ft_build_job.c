#include "minishell.h"

static int		ft_expand_scape(char **res, char **cmd, size_t *pos,
	char single_quote, char quote)
{
	(void)single_quote;
	(void)quote;
	*((*res) + *pos) = **cmd;
	(*cmd)++;
	(*pos)++;
	return (1);
}

static int		ft_expand_dollar(abs_struct *base, char **res, size_t *len, size_t *pos, char **cmd)
{
	(void)base;
	(void)res;
	(void)len;
	(void)pos;
	(void)cmd;
	return (1);
}

static char		*expand(abs_struct *base, char *cmd)
{
	char		*res;
	size_t		len;
	size_t		pos;
	char		quote;
	char		single_quote;
	int			scape;

	len = (!cmd ? 0 : ft_strlen(cmd));
	if (!len || !(res = ft_calloc(len + 2, sizeof(char))))
		return (0);
	pos = 0;
	single_quote = 0;
	quote = 0;
	scape = 0;
	while (cmd && *cmd != '\0')
	{
		if (scape)
		{
			if (!ft_expand_scape(&res, &cmd, &pos, single_quote, quote))
			{
				free(res);
				return (0);
			}
			scape = 0;
		}
		else if (*cmd == '\'' && !quote)
		{
			single_quote = (!single_quote ? '\'' : 0);
			*(res + pos++) = *cmd;
		}
		else if (*cmd == '"' && !single_quote && !scape)
		{
			quote = (!quote ? '"' : quote);
			*(res + pos++) = *cmd;
		}
		else if (*cmd == '$' && (quote || !single_quote))
		{
			ft_expand_dollar(base, &res, &len, &pos, &cmd);
		}
		else if (*cmd == '\\')
		{
			scape = (scape ? 0 : 1);
			*(res + pos++) = *cmd;
		}
		else
			*(res + pos++) = *cmd;
		cmd++;
	}
	*(res + pos) = ' ';
	return (res);
}

static char		*ft_expand_cmd(abs_struct *base, char *command)
{
	char		*output;
	char		*expanded_slice;
	char		*to_expand;
	char		*tmp;

	output = 0;
	while ((to_expand = ft_split_shell_by(&command, " ")))
	{
		if (!(expanded_slice = expand(base, to_expand)) ||
			!(tmp = ft_strjoin(output, expanded_slice)))
		{
			free(to_expand);
			if (expanded_slice)
				free(expanded_slice);
			if (output)
				free(output);
			return (0);
		}
		free(to_expand);
		free(expanded_slice);
		free(output);
		output = tmp;
	}
	return (output);
}

t_job			*ft_build_job(abs_struct *base, char *command)
{
	t_job		*j;
	char		*cmd;

	if (!command || !(*command) || !(j = ft_calloc(1, sizeof(t_job))))
		return (0);
	j->command = command;
	j->std_fds.errfile = STDERR_FILENO;
	j->std_fds.infile = STDIN_FILENO;
	j->std_fds.outfile = STDOUT_FILENO;
	cmd = ft_expand_cmd(base, command);
	j->first_process = ft_build_processes(cmd);
	if (cmd)
		free(cmd);
	return (j);
}
