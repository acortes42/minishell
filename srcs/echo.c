/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:27 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:04:28 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo(abs_struct *base)
{
    int i;

    i = base->actual_argument + 1;
    if (ft_strcmp(base->parseString[i], "$?") == 0)
    {
        ft_putnbr(base->error);
        ft_putstr("\n");
        return (1);
    }
    while (base->parseString[i])
    {
        if (ft_strcmp(base->parseString[i], "|") != 0 && ft_strcmp(base->parseString[i], ";") != 0)
        {
            ft_putstr(base->parseString[i]);
            i++;
            base->actual_argument++;
        }
        else
        {
            if (ft_strcmp(base->parseString[i], "|") != 0 )
            base->flag = 1;
            break;
        }
    }
    ft_putstr("\n");
    base->error = 0;
    return (1);
}