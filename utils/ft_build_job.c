#include "minishell.h"

static char		*ft_expand_slice(abs_struct *base, char *slice)
{
	char		*tmp;
	char		*token;
	char		**splitted;
	int			len;
	int			quote;

	quote = 0;
	len = 0;
	while ((token = ft_split_shell_by(&slice, "'")))
	{
		if (quote)
		{
			ft_array_add(&splitted, &len, token);
			if (*slice == '\'')
				ft_array_add(&splitted, &len, ft_strdup("'"));
		}
		else
		{
			if (*token != '\0')
				ft_array_add(&splitted, &len, ft_expand_dollar(token));
			free(token);
			if (*slice == '\'')
				ft_array_add(&splitted, &len, ft_strdup("'"));
		}
	}

	return (out);
}

static char		*expand(abs_struct *base, char *cmd)
{
	char		*res;
	size_t		len;
	char		quote;
	char		single_quote;
	int			scape;

	len = (!cmd ? 0 : ft_strlen(cmd));
	if (!len || !(res = ft_calloc(len, sizeof(char))))
		return (0);
	single_quote = 0;
	quote = 0;
	scape = 0;
	while (cmd && *cmd != '\0')
	{
		if (*cmd == '\'')
		{
			single_quote = (!single_quote ? '\'' : 0);
		}
		else if (*cmd == '"')
		{
			quote = (!quote ? '"' : quote);
		}
		else if (*cmd == '$')
		{
			ft_expand_dollar(&res, &len, &cmd);
		}
		else if (*cmd == '\\')
		{
			scape = (scape ? 0 : 1);
			if (!scape && (quote || !single_quote))
				ft_expand_scape(&res, &cmd);
		}
		cmd++;
	}
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
		if (!(expanded_slice = ft_expand_slice(base, to_expand)) ||
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
