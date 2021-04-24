/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:33:03 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/21 12:49:30 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	append_new_line(char **str)
{
	char			*tmp;

	if (!str || !(*str))
		return (0);
	tmp = ft_strjoin(*str, "\n");
	if (!tmp)
		return (0);
	free(*str);
	*str = tmp;
	return (1);
}

int	obtain_full_line(t_abs_struct *base)
{
	int				found_new_line;

	if (base->input)
		free(base->input);
	base->input = 0;
	found_new_line = 0;
	while (!found_new_line && (!base->input || *base->input))
	{
		found_new_line = get_next_line(STDIN_FILENO, &base->input, base);
		if (found_new_line < 0)
			ft_exit_minishell(base, 2);
	}
	if (base->input && found_new_line && !append_new_line(&base->input))
		ft_exit_minishell(base, 1);
	if (ft_strlen(base->input) >= 1 && ft_strcmp(base->input, "\n"))
		ft_write_history_line(base);
	return (0);
}

static void	execute_command_read(t_abs_struct *base)
{
	base->first_job = ft_build_jobs(base->input);
	while (base->first_job)
	{
		ft_launch_job(base, base->first_job);
		base->first_job = ft_release_job(base->first_job);
	}
}

unsigned int	ft_getlflag(int fd)
{
	struct termios	settings;
	unsigned int	result;

	if (tcgetattr (fd, &settings) < 0)
	{
		perror ("error in tcgetattr");
		return 0;
	}
	result = settings.c_lflag;
	return (result);
}

int	main(int argc, char **argv, char **envp)
{
	int				minishell_ready;
	t_abs_struct 	base;

	(void)argc;
	(void)argv;
	ft_memset(&base, 0, sizeof(t_abs_struct));
	minishell_ready = ft_init_minishell(&base, envp);
	if (minishell_ready)
		clear_screen();
	base.c_lflag = ft_getlflag(STDIN_FILENO); // Keep c_lflag value before changing anything
	if (!ft_setlflag(STDIN_FILENO, 0, ICANON|ECHO))
		ft_exit_minishell(&base, 1); // Exit minishell: Not disabled canonical input and echoing
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
