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

static int	ft_extract_fields(char *cmd, char ***argv)
{
	int				fields;
	char			*field;
	char			*tmp;

	fields = 0;
	field = ft_split_shell_by(&cmd, " ");
	while (field)
	{
		if (*field != '\n')
		{
			tmp = ft_trim(field);
			if (tmp)
			{
				if (!ft_array_add(argv, &fields, tmp))
				{
					free(field);
					return (-1);
				}
			}
		}
		free(field);
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
