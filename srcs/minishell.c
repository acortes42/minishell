/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:33:03 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:28:03 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int obtain_full_line(abs_struct *base)
{
	char        c;
	int         fd;
	int         i;

	fd = open("history.txt", O_RDWR | O_APPEND);
	i = 0;
	while (read(0, &c, sizeof(char)) > 0)
	{
		write(fd, &c, 1);
		if (c == '\n')
			break;
		if (c != '\"' && c != '\'')
		{
			base->string[i] = c;
			i++;
		}
	}
	base->string[i] = '\0';
	close(fd);
	ft_array_release(base->parseString);
	base->parseString = ft_split(base->string, ' ');
	return (0);
}

int execute (abs_struct *base)
{   
	pid_t   pid;

	pid = fork();

	if (pid > 0)
		wait(&pid);
	else if (pid == 0)
	{
		ft_execute_command(base);
		// TODO: Este exit debería ser el valor de retorno de la operación el que devuelve $?...
		exit(0);
    }
	else
		ft_putstr("\e[0mError en la creacion de subproceso\n");
	return (1);
}

int main(int argc, char **argv, char **envp)
{
	int         minishell_ready;
	abs_struct  base;

	(void)argc;
	(void)argv;
	minishell_ready = ft_init_minishell(&base, envp);
	if (minishell_ready)
		clearScreen();
	while (minishell_ready)
	{
		ft_putstr("\e[92m--->");
		obtain_full_line(&base);
		ft_execute_command(&base);
	}
	return (0);
}