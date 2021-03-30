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

int					obtain_full_line(t_abs_struct *base)
{
	int				fd;
	int				found_new_line;
	char			*tmp;

	fd = open("history.txt", O_RDWR | O_APPEND);
	if (base->input)
		free(base->input);
	base->input = 0;
	found_new_line = 0;
	while (!found_new_line)
	{
		found_new_line = get_next_line(STDIN_FILENO, &base->input);
		if (found_new_line < 0)
			ft_exit_minishell(base, 2);
	}
	if (!base->input || !(tmp = ft_strjoin(base->input, "\n")))
		ft_exit_minishell(base, 1);
	free(base->input);
	base->input = tmp;
	write(fd, base->input, ft_strlen(base->input));
	close(fd);
	return (0);
}

static void			execute_command_read(t_abs_struct *base)
{
	t_job			*job;

	job = ft_build_jobs(base->input);
	base->first_job = job;
	while (job)
	{
		ft_launch_job(base, job);
		job = ft_release_job(job);
		base->first_job = job;
	}
}

int					main(int argc, char **argv, char **envp)
{
	int				minishell_ready;
	t_abs_struct	base;

	(void)argc;
	(void)argv;
	ft_memset(&base, 0, sizeof(t_abs_struct));
	minishell_ready = ft_init_minishell(&base, envp);
	if (minishell_ready)
		clear_screen();
	while (minishell_ready)
	{
		ft_show_prompt(&base);
		obtain_full_line(&base);
		execute_command_read(&base);
		base.first_job = 0;
		base.num_args = 0;
		base.parse_string = 0;
	}
	return (0);
}
