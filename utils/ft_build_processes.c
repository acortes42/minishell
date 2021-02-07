#include "minishell.h"

static char			*ft_trim(char *str)
{
	char			*i;

	if (!str)
		return (str);
	i = str + ft_strlen(str) - 1;
	while (i >= str && ft_isspace(*i))
	{
		*i = '\0';
		i--;
	}
	return (str);
}

static char			**ft_extract_fields(char *expanded_cmd)
{
	char			**fields;

	// TODO: Este split tiene que tener en cuenta más factores
	if (!expanded_cmd)
		return (0);
	if (!(fields = ft_split(expanded_cmd, ' ')))
		return (0);
	if (!ft_array_len(fields))
	{
		free(fields);
		return (0);
	}
	return (fields);
}

t_process			*ft_build_ctrl_d_process(void)
{
	t_process		*proc;

	if (!(proc = ft_calloc(1, sizeof(t_process))))
		return (0);
	proc->argv = 0;
	return (proc);
}

t_process			*ft_build_process(char ***fields)
{
	t_process		*proc;
	size_t			process_len;
	size_t			i;

	if (!(proc = ft_calloc(1, sizeof(t_process))))
		return (0);
	process_len = 0;
	while (*fields && *(*fields + process_len) &&
		(**(*fields + process_len) != ';' ||
		**(*fields + process_len) != '\0'))
		process_len++;
	if (!(proc->argv = ft_calloc(process_len + 1, sizeof(char *))))
	{
		free(proc);
		return (0);
	}
	i = 0;
	while (i < process_len)
	{
		*(proc->argv + i) = ft_trim(**fields);
		(*fields)++;
		i++;
	}
	if (**fields && ***fields != '\0')
		(*fields)++;
	return (proc);
}

t_process			*ft_build_processes(char *expanded_cmd)
{
	t_process		*procs;
	t_process		*proc_tmp;
	char			**fields;
	char			**tmp;

	fields = ft_extract_fields(expanded_cmd);
	if (!ft_array_len(fields))
	{
		ft_array_release(fields);
		return (ft_build_ctrl_d_process());
	}
	if (ft_array_len(fields)==1 && **fields == '\n')
	{
		ft_array_release(fields);
		return (0);
	}
	procs = 0;
	tmp = fields;
	while (*tmp)
	{
		if (!procs)
		{
			procs = ft_build_process(&tmp);
			proc_tmp = procs;
		}
		else
		{
			proc_tmp->next = ft_build_process(&tmp);
			proc_tmp = proc_tmp->next;
		}
	}
	free(fields);
	return (procs);
}
