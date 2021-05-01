/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_history_line.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:57:44 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/01 16:57:45 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_history_line(t_abs_struct *base)
{
	int	fd;

	fd = ft_open_history(base, O_RDWR | O_APPEND);
	if (fd < 0)
		return ;
	write(fd, base->input, ft_strlen(base->input));
	close(fd);
	base->history_lines++;
	base->current_history_line = base->history_lines + 1;
}
