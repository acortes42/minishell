/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_default_signals.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 16:18:43 by visv              #+#    #+#             */
/*   Updated: 2021/04/01 14:13:09 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_signals_1(void)
{
	return (0);
}

static int	set_signals_2(void)
{
	return (0);
}

int	ft_set_default_signals(void)
{
	int			ret;

	ret = set_signals_1();
	if (ret)
		return (ret);
	ret = set_signals_2();
	if (ret)
		return (ret);
	return (0);
}
