#include "minishell.h"

static void	perform_environment_update(t_env_update *info)
{
	extern t_abs_struct	g_base;

	if (!info->changed_dir)
	{
		info->p->status = 127;
		g_base.last_status = info->p->status;
		if (info->old_pwd)
			free(info->old_pwd);
		info->old_pwd = ft_strdup(ft_getenv(g_base.env, "PWD") + 4);
		ft_update_environment_pwds(info->old_pwd, info->home);
	}
	else
	{
		info->p->status = 0;
		g_base.last_status = info->p->status;
		ft_update_environment_pwds(info->old_pwd, info->pwd);
	}
	if (info->pwd)
		free(info->pwd);
	if (info->old_pwd)
		free(info->old_pwd);
}

static void	print_file_doesnt_exist(char *file)
{
	ft_putstr_fd("\e[0mcd: ", STDERR_FILENO);
	if (file)
		ft_putstr_fd(file, STDERR_FILENO);
	ft_putstr_fd(": File or dir doesn't exist\n", STDERR_FILENO);
}

void	perform_chdir_and_environment_update(t_process *p, char *home)
{
	t_env_update		info;
	char				*path;

	info.pwd = 0;
	info.old_pwd = getcwd(0, 0);
	info.changed_dir = !chdir(home);
	if (!info.changed_dir)
	{
		path = get_first_non_empty_arg(p->argv + 1);
		print_file_doesnt_exist(path);
	}
	info.pwd = getcwd(0, 0);
	if (!info.pwd)
	{
		ft_putstr_fd(strerror(errno), STDERR_FILENO);
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	info.home = home;
	info.p = p;
	perform_environment_update(&info);
}
