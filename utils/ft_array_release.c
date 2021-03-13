/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_release.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:17:11 by visv              #+#    #+#             */
/*   Updated: 2021/03/13 16:17:13 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_array_release(char **envp)
{
	char		**tmp;

	if (!envp)
		return ;
	tmp = envp;
	while (tmp && *tmp)
	{
		free(*tmp);
		tmp++;
	}
	free(envp);
}
