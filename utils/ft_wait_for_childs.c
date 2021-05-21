#include "minishell.h"

static void	look_for_first_process_not_completed(t_job *j, t_process **curr)
{
	t_process	*tmp;

	tmp = j->first_process;
	while (tmp)
	{
		if (!tmp->completed)
		{
			*curr = tmp;
			break ;
		}
		tmp = tmp->next;
	}
}

static void	ft_close_job(t_job *j, int kill_childs)
{
	t_process	*curr;

	curr = j->first_process;
	while (curr)
	{
		if (!curr->completed && kill_childs)
			kill(curr->pid, 9);
		curr = curr->next;
	}
}

void	ft_wait_for_process(t_process *curr)
{
	extern t_abs_struct	g_base;
	pid_t				pid;


	if (!curr->pid || curr->completed)
		return ;
	pid = waitpid(curr->pid, &curr->status, WNOHANG);
	if (pid > 0 && WIFEXITED(curr->status))
	{
		curr->completed = 1;
		curr->status = ft_adjust_exit_value(WEXITSTATUS(curr->status));
		g_base.last_status = curr->status;
	}
}

void	ft_wait_for_childs(t_job *j)
{
	t_process		*curr;

	curr = j->first_process;
	while (true)
	{
		if (!curr)
		{
			look_for_first_process_not_completed(j, &curr);
			if (!curr)
				break ;
		}
		ft_wait_for_process(curr);
		if (curr->completed && curr->status != 0)
			break ;
		curr = curr->next;
	}
	ft_close_job(j, curr && curr->status != 0);
}
