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

int echo(abs_struct *base, t_process *p)
{
    int i;
    int flag;

    i = 1;
    flag = 0;
    if (!p->argv[i])
        return (1);
    flag = (ft_strcmp(p->argv[i], "-n") == 0) ? 0 : 1;
    if (flag == 0)
        i++;
    if (!p->argv[i])
        return (1);

    while (p->argv[i])
    {
        if (ft_strcmp(p->argv[i], "|") != 0 && ft_strcmp(p->argv[i], ";") != 0 &&
			ft_strcmp(p->argv[i], "<") != 0 && ft_strcmp(p->argv[i], ">") != 0 &&
			ft_strcmp(p->argv[i], ">>") != 0)
        {
            ft_putstr(p->argv[i]);
            ft_putstr(" ");
            i++;
        }
        else
        {
            if (ft_strcmp(p->argv[i], "|") != 0 )
                base->flag = 1;
            break;
        }
    }
    if (flag == 1)
        ft_putstr("\n");
    base->error = 0;
    return (1);
}