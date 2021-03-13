/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mark_job_as_running.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:21 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:18:22 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_mark_job_as_running (t_job *j)
{
	t_process	*p;

	if (!j)
		return ;
	for (p = j->first_process; p; p = p->next)
		p->stopped = 0;
  	j->notified = 0;
}


