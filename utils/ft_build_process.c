#include "minishell.h"

static void			remove_quotes(char *field)
{
	size_t			len;
	size_t			pos;

	len = ft_strlen(field);
	if (!len)
		return ;
	if ((*field != '"' || *(field + len - 1) != '"') &&
		(*field != '\'' || *(field + len - 1) != '\''))
		return ;
	pos = 1;
	while (*(field + pos) && pos < (len - 1))
	{
		*(field + pos - 1) = *(field + pos);
		pos++;
	}
	*(field + pos - 1) = *(field + len);
}

static int			ft_extract_fields(char *expanded_cmd, char ***argv)
{
	int				fields;
	char			*field;
	char			*tmp;

	fields = 0;
	while ((field = ft_split_shell_by(&expanded_cmd, " ")))
	{
		if (*field != '\n')
		{
			tmp = ft_trim(field);
			remove_quotes(tmp);
			free(field);
			if (!tmp)
				continue ;
			field = tmp;
		}
		if (!ft_array_add(argv, &fields, field))
			return (-1);
	}
	return (fields);
}

t_process			*ft_build_process(char *expanded_cmd)
{
	t_process		*proc;
	int				fields;

	if (!(proc = ft_calloc(1, sizeof(t_process))))
		return (0);
	fields = ft_extract_fields(expanded_cmd, &proc->argv);
	if (fields < 0)
	{
		ft_release_process(proc);
		return (0);
	}
	else if (!fields)
		return (proc);
	else if (fields == 1 && (proc->argv && *proc->argv && **proc->argv == '\n'))
	{
		ft_release_process(proc);
		return (0);
	}
	return (proc);
}
