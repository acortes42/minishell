#include "minishell.h"

static void	look_for_first_process_not_completed(t_job *j, t_process **prev,
				t_process **curr)
{
	t_process	*tmp_prev;
	t_process	*tmp;

	tmp_prev = 0;
	tmp = j->first_process;
	while (tmp)
	{
		if (!tmp->completed)
		{
			*prev = tmp_prev;
			*curr = tmp;
			break ;
		}
		tmp_prev = tmp;
		tmp = tmp->next;
	}
}

static void	ft_close_job(t_job *j, int kill_childs)
{
	t_process	*prev;
	t_process	*curr;

	prev = 0;
	curr = j->first_process;
	while (curr)
	{
		ft_close_pipes(prev, curr);
		if (!curr->completed && kill_childs)
			kill(curr->pid, 9);
		prev = curr;
		curr = curr->next;
	}
}

void	ft_wait_for_process(t_process *curr)
{
	extern t_abs_struct	g_base;

	if (!curr->pid || curr->completed)
		return ;
	curr->completed = waitpid(curr->pid, &curr->status, WNOHANG);
	if (curr->completed && WIFEXITED(curr->status))
	{
		curr->status = ft_adjust_exit_value(WEXITSTATUS(curr->status));
		g_base.error = curr->status;
	}
}

void	ft_wait_for_childs(t_job *j)
{
	t_process		*curr;
	t_process		*prev;

	prev = 0;
	curr = j->first_process;
	while (true)
	{
		if (!curr)
		{
			look_for_first_process_not_completed(j, &prev, &curr);
			if (!curr)
				break ;
		}
		ft_wait_for_process(curr);
		if (curr->completed && curr->status != 0)
			break ;
		prev = curr;
		curr = curr->next;
	}
	ft_close_job(j, curr && curr->status != 0);
}
