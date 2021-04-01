/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_aux.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 17:54:04 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 18:07:13 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_home(char *home)
{
	if (home)
		return (0);
	return (1);
}

int	ft_check_home2(char *home)
{
	if (home)
		return (-1);
	return (0);
}
