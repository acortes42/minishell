#include "minishell.h"

static int			ft_extract_fields(char *cmd, char ***argv)
{
	int				fields;
	char			*field;
	char			*tmp;

	fields = 0;
	while ((field = ft_split_shell_by(&cmd, " ")))
	{
		if (*field != '\n')
		{
			tmp = ft_trim(field);
			free(field);
			if (!tmp)
				continue ;
			field = tmp;
			if (!ft_array_add(argv, &fields, field))
				return (-1);
		}
	}
	return (fields);
}

t_process			*ft_build_process(char *cmd)
{
	t_process		*proc;
	int				fields;

	if (!(proc = ft_calloc(1, sizeof(t_process))))
		return (0);
	fields = ft_extract_fields(cmd, &proc->argv);
	if (fields < 0)
	{
		ft_release_process(proc);
		return (0);
	}
	else if (!fields)
		return (proc);
	else if (fields == 1 &&
		(proc->argv && *proc->argv && **proc->argv == '\n'))
	{
		ft_release_process(proc);
		return (0);
	}
	return (proc);
}
