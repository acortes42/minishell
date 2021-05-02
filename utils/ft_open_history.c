/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_history.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:29:19 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/01 16:29:28 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_open_history(t_abs_struct *base, int mode)
{
	char		*history_path;
	char		*home;
	int			fd;

	if (!base)
		return (-1);
	home = ft_getenv(base->env, "PWD") + 4;
	if (ft_strlen(home) == 4)
		return (-1);
	history_path = ft_strjoin(home, "/history_visv.txt");
	if (!history_path)
		return (-1);
	fd = open(history_path, mode | O_CREAT, S_IRUSR | S_IWUSR);
	free(history_path);
	return (fd);
}
