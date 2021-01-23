/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:24 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:04:25 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
    Parece que llega donde tiene que llegar pero falla con el chdir
*/

int cd(abs_struct *base)
{
    char    cwd[PATH_MAX];
    char    *str;

    if (base->num_args == base->actual_argument + 1)
    {
        chdir("/");
        base->error = 0;
    }
    else if (base->parseString[base->actual_argument + 1][0] == '/')
    {
        if (chdir(base->parseString[1]) == 0)
        {
            ft_putstr("\e[0mBusqueda de directorio correcta\n");
            chdir(base->parseString[1]);
            base->error = 0;
        }
        else
        {
            ft_putstr("\e[0mError a la asignación de directorio\n");
            base->error = 1;
        }
    }
    else if (strcmp(base->parseString[base->actual_argument + 1], "..") == 0)
    {
        chdir("..");
        ft_putstr("\e[0mTira hacia atrás\n");
        base->error = 0;
    }
    else
    {
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            str = strdup(getcwd(cwd, sizeof(cwd)));
            str = ft_strjoin(str, "/");
            str = ft_strjoin(str, base->parseString[base->actual_argument + 1]);
            if (chdir(str) == 0)
            {
                ft_putstr("\e[0mDirectorio valido\n");
                base->error = 0;
            }
            else
            {
                ft_putstr("\e[0mFallo al acceder al directorio\n");
                base->error  = 1;
            }
        }
        else
        {
            ft_putstr("\e[0mDirectorio no valido\n");
            base->error  = 1;
        }
    }
    return (1);
}