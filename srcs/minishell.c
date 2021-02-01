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
	int         exceptionNum;
	abs_struct  *base;

	signal(SIGINT, handle_sigint);
	exceptionNum = 1;
	clearScreen();
	if (!(base = malloc(sizeof(abs_struct))))
	  	return (-1);
	ft_memset(base, 0, sizeof(abs_struct));
	// TODO: eliminar el valid_str? Creo que solo aporta confusion a la hora de entender los else if y puntos de error si no encajan los indices
	base->valid_str = ft_split("exit echo pwd cd history help env setenv unsetenv clear export", ' ');
	ft_copy_env(base, envp);
	base->actual_argument = 0;
	base->flag = 0;
	base->error = 0;
	while (exceptionNum == 1)
	{
		ft_putstr("\e[92m--->");
		obtain_full_line(base);
		ft_execute_command(base);
	}
	// TODO: Release base struct
	ft_release_base(base);
	(void)argc;
	(void)argv;
	return (0);
}