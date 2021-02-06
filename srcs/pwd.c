/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:40 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:04:41 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_pwd()
{
   char cwd[PATH_MAX];
   
   if (getcwd(cwd, sizeof(cwd)) != NULL)
   {
       ft_putstr(cwd);
       ft_putstr("\n");
   }
   else 
       perror("getcwd() error");
   return (1);
}

int     ft_help()
{
    ft_putstr("\e[0mLos comandos disponibles són los siguientes:\n\n");
	ft_putstr("exit\necho\npwd\ncd\nhistory\nhelp\nenv\nsetenv\nunsetenv\nclear\nexport\n");
    return(1);
}
