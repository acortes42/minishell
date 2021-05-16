#include "minishell.h"

static void	perform_environment_update(t_env_update *info)
{
	extern t_abs_struct	g_base;

	if (!info->changed_dir)
	{
		info->p->status = 127;
		if (info->old_pwd)
			free(info->old_pwd);
		info->old_pwd = ft_strdup(ft_getenv(g_base.env, "PWD") + 4);
		ft_update_environment_pwds(info->old_pwd, info->home);
	}
	else
	{
		info->p->status = 0;
		ft_update_environment_pwds(info->old_pwd, info->pwd);
	}
	if (info->pwd)
		free(info->pwd);
	if (info->old_pwd)
		free(info->old_pwd);
}

static void	print_file_doesnt_exist(char *file)
{
	ft_putstr("\e[0mcd: ");
	if (file)
		ft_putstr(file);
	ft_putstr(": File or dir doesn't exist\n");
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
		ft_putstr(strerror(errno));
		ft_putstr("\n");
	}
	info.home = home;
	info.p = p;
	perform_environment_update(&info);
}
