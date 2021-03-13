/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_release_base.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:29 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:18:30 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_release_base(t_abs_struct *base)
{
	if (!base)
		return ;
	ft_array_release(base->env);
	// Este se libera al liberar el job
	base->parse_string = 0;
	ft_release_jobs(base->first_job);
	base->first_job = 0;
	return ;
}

