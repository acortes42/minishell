#include "minishell.h"

static int	is_number(char *ignoreeof)
{
	int		is_num;

	if (!ignoreeof)
		return (0);
	is_num = 1;
	while (ignoreeof && *ignoreeof && is_num)
	{
		is_num = ft_isdigit(*ignoreeof);
		ignoreeof++;
	}
	return (is_num);
}

static int	determine_ctrl_d_times(abs_struct *base)
{
	char	*ignoreeof;

	ignoreeof = ft_getenv(base->env, "IGNOREEOF");
	if (!ignoreeof)
		return (0);
	else
	{
		ignoreeof += 10;
		if (!is_number(ignoreeof))
			return (10);
		else
			return (ft_atoi(ignoreeof));
	} 
}

int			ft_execute_ctrl_d(abs_struct *base)
{
	int		ctrl_d_times;
	
	base->ctrl_d_times++;
	ctrl_d_times = determine_ctrl_d_times(base);
	if (ctrl_d_times < base->ctrl_d_times)
	{
		ft_putstr("exit\n");
		ft_exit_minishell(base, 0);
	}
	ft_putstr("\e[0mUse <<exit>> to close shell\n");
	return (1);
}