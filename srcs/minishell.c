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
		base->string[i] = c;
		i++;
		if (c == '\n')
			break;
	}
	base->string[i] = '\0';
	close(fd);
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

static void		launch_jobs(abs_struct *base)
{
	t_job		*job;

	job = ft_build_jobs(base->string);
	while (job) {
		base->first_job = job;
		ft_launch_job(base, job);
		job = ft_free_job(job);
	}

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
		ft_show_prompt(&base);
		obtain_full_line(&base);
		launch_jobs(&base);
		base.first_job = 0;
		base.num_args = 0;
		base.parseString = 0;
	}
	return (0);
}