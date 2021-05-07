#include "minishell.h"

void	ft_update_environment_pwds(char *old_pwd, char *pwd)
{
	extern t_abs_struct	g_base;

	if (!ft_getenv(g_base.env, "PWD"))
		ft_array_add(&g_base.env, &g_base.lines_envp,
			ft_strjoin("PWD=", pwd));
	else
		ft_array_update(&g_base.env, &g_base.lines_envp, "PWD", pwd);
	if (!ft_getenv(g_base.env, "OLDPWD"))
	{
		ft_array_add(&g_base.env, &g_base.lines_envp,
			ft_strjoin("OLDPWD=", old_pwd));
	}
	else
		ft_array_update(&g_base.env, &g_base.lines_envp, "OLDPWD", old_pwd);
}
