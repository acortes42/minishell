/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_release_job.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:36 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 14:14:49 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_job	*ft_release_job(t_job *j)
{
	t_job			*j_next;
	t_process		*p;

	if (!j)
		return (0);
	j_next = j->next;
	j->next = 0;
	p = j->first_process;
	j->first_process = 0;
	p = ft_release_process(p);
	while (p)
		p = ft_release_process(p);
	if (j->command)
		free(j->command);
	free(j);
	return (j_next);
}
