/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_build_process.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:34 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 15:51:07 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_extract_redirs_from_field(char *field_to_split, char ***argv,
				int *fields)
{
	char	*field;
	char	*field_to_split_iterator;

	field_to_split_iterator = field_to_split;
	field = ft_split_shell_process(&field_to_split_iterator);
	while (field)
	{
		if (*field == '\n')
			free(field);
		else
		{
			if (!ft_array_add(argv, fields, field))
			{
				free(field);
				free(field_to_split);
				return (-1);
			}
		}
		field = ft_split_shell_process(&field_to_split_iterator);
	}
	free(field_to_split);
	return (1);
}

static int	append_field_to_argv(char *field_to_append, char ***argv,
				int *fields)
{
	char	*tmp;

	if (!field_to_append)
		return (1);
	tmp = ft_trim(field_to_append);
	if (!tmp)
		free(field_to_append);
	else
	{
		free(field_to_append);
		if (!ft_array_add(argv, fields, tmp))
			return (-1);
	}
	return (1);
}

static int	ft_extract_fields(char *cmd, char ***argv)
{
	int				fields;
	char			*field;

	fields = 0;
	field = ft_split_shell_by(&cmd, " ");
	while (field)
	{
		if (*field == '\n')
			free(field);
		else
		{
			if (field_contains_redirs(field))
			{
				if (ft_extract_redirs_from_field(field, argv, &fields) < 0)
					return (-1);
			}
			else
			{
				if (append_field_to_argv(field, argv, &fields) < 0)
					return (-1);
			}
		}
		field = ft_split_shell_by(&cmd, " ");
	}
	return (fields);
}

t_process	*ft_build_ctrl_d_process(void)
{
	t_process		*proc;

	proc = ft_calloc(1, sizeof(t_process));
	if (!(proc))
		return (0);
	proc->ctrl_d = 1;
	return (proc);
}

t_process	*ft_build_process(char *cmd)
{
	t_process		*proc;
	int				fields;

	proc = ft_calloc(1, sizeof(t_process));
	if (!(proc))
		return (0);
	fields = ft_extract_fields(cmd, &proc->argv);
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
