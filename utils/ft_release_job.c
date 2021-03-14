/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_release_job.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:36 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:18:37 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job				*ft_release_job(t_job *j)
{
	t_job			*j_next;
	t_process		*p;
	t_process		*p_next;

	if (!j)
		return (0);
	j_next = j->next;
	j->next = 0;
	p = j->first_process;
	while ((p_next = ft_release_process(p)))
		p = p_next;
	j->first_process = 0;
	if (j->command)
		free(j->command);
	free(j);
	return (j_next);
}
