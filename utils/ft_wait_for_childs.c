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

static void	ft_wait_for_process(t_process *curr, int *kill_childs)
{
	extern t_abs_struct	g_base;

	curr->completed = waitpid(curr->pid, &curr->status, WNOHANG);
	if (curr->completed && WIFEXITED(curr->status))
	{
		if (WEXITSTATUS(curr->status))
		{
			*kill_childs = 1;
			return ;
		}
		curr->status /= 256;
		g_base.error = curr->status;
	}
}

void	ft_wait_for_childs(t_job *j)
{
	int				kill_childs;
	t_process		*curr;
	t_process		*prev;

	kill_childs = 0;
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
		ft_wait_for_process(curr, &kill_childs);
		if (kill_childs)
			break ;
		prev = curr;
		curr = curr->next;
	}
	ft_close_job(j, kill_childs);
}
