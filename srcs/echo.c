/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:27 by acortes-          #+#    #+#             */
/*   Updated: 2021/03/02 17:51:08 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int echo(abs_struct *base)
{
	(void)base;
	ft_putstr("TODO: Recuperar echo pero utilizando t_process");
	return (1);	
/*     int i;
    int flag;

    i = 1;
    flag = 0;
    if (!base->parseString[i])
        return (1);
    flag = (ft_strcmp(base->parseString[i], "-n") == 0) ? 0 : 1;
    if (flag == 0)
        i++;
    if (!base->parseString[i])
        return (1);

    while (base->parseString[i])
    {
        if (ft_strcmp(base->parseString[i], "|") != 0 && ft_strcmp(base->parseString[i], ";") != 0 &&
			ft_strcmp(base->parseString[i], "<") != 0 && ft_strcmp(base->parseString[i], ">") != 0 &&
			ft_strcmp(base->parseString[i], ">>") != 0)
        {
            ft_putstr(base->parseString[i]);
            ft_putstr(" ");
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
    if (flag == 1)
        ft_putstr("\n");
    base->error = 0;
    return (1);
 */}