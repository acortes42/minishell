/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:33:03 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/15 14:55:10 by acortes-         ###   ########.fr       */
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

int	obtain_full_line(void)
{
	extern t_abs_struct	g_base;
	int					found_new_line;
	char				*trimmed_input;

	if (g_base.input)
		free(g_base.input);
	g_base.input = 0;
	found_new_line = 0;
	while (!found_new_line && (!g_base.input || *g_base.input))
	{
		found_new_line = get_next_line(STDIN_FILENO, &g_base.input, &g_base);
		if (found_new_line < 0)
			ft_exit_minishell(2);
	}
	if (g_base.input && found_new_line && !append_new_line(&g_base.input))
		ft_exit_minishell(1);
	trimmed_input = ft_trim(g_base.input);
	if (ft_strlen(g_base.input) >= 1 && ft_strcmp(trimmed_input, "\n") \
			&& ft_isascii(g_base.input[0]))
		ft_write_history_line(&g_base);
	if (trimmed_input)
		free(trimmed_input);
	return (0);
}

static void	execute_command_read(t_abs_struct *base)
{
	if (!ft_setlflag(STDIN_FILENO, 1, g_base.c_lflag))
		ft_exit_minishell(1);
	if (check_base_syntatic_errors(base->input))
		ft_putstr_fd("Error sintáctico en el comando\n", STDERR_FILENO);
	else
	{
		base->first_job = ft_build_jobs(base->input);
		while (base->first_job)
		{
			signal(SIGINT, forked_process_signal_handler);
			signal(SIGQUIT, forked_process_signal_handler);
			dup_std_fds(&base->std_fds);
			ft_launch_job(base, base->first_job);
			base->first_job = ft_release_job(base->first_job);
			restore_std_fds(&base->std_fds);
			signal(SIGINT, signal_handler);
			signal(SIGQUIT, signal_handler);
		}
	}
	if (!ft_setlflag(STDIN_FILENO, 0, ICANON | ECHO | IEXTEN))
		ft_exit_minishell(1);
}

int	main(int argc, char **argv, char **envp)
{
	int					minishell_ready;
	extern t_abs_struct	g_base;

	(void)argc;
	(void)argv;
	ft_memset(&g_base, 0, sizeof(t_abs_struct));
	minishell_ready = ft_init_minishell(&g_base, envp);
	if (minishell_ready)
		ft_clear_screen();
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (minishell_ready)
	{
		ft_show_prompt(&g_base);
		obtain_full_line();
		execute_command_read(&g_base);
		g_base.first_job = 0;
		g_base.num_args = 0;
		g_base.parse_string = 0;
	}
	return (0);
}
