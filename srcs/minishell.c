/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:33:03 by acortes-          #+#    #+#             */
/*   Updated: 2021/02/15 17:01:30 by acortes-         ###   ########.fr       */
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

static void		execute_command_read(abs_struct *base)
{
	t_job		*job;

	job = ft_build_jobs(base->string);
	while (job) {
		base->first_job = job;
		ft_launch_job(base, job);
		job = ft_release_job(job);
	}
}

int main(int argc, char **argv, char **envp)
{
	int         minishell_ready;
	abs_struct  *base;

	if (!(base = ft_calloc(1, sizeof(abs_struct))))
		ft_exit_minishell(0, 1);
	(void)argc;
	(void)argv;
	minishell_ready = ft_init_minishell(base, envp);
	if (minishell_ready)
		clearScreen();
	while (minishell_ready)
	{
		ft_show_prompt(base);
		obtain_full_line(base);
		execute_command_read(base);
		base->first_job = 0;
		base->num_args = 0;
		base->parseString = 0;
	}
	free(base);
	return (0);
}