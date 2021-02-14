#include "minishell.h"

static char		*ft_get_cwd(abs_struct *base)
{
	char		*cwd;

	cwd = getcwd(0, 0);
	if (!cwd || *cwd == '(')
	{
		if (cwd)
			free (cwd);
		ft_exit_minishell(base, errno);
	}
	return (cwd);
}

static void		ft_show_prompt_cwd(abs_struct *base)
{
	char		*cwd;
	char		*tmp;
	size_t		len;
	char		*home;

	cwd = ft_get_cwd(base);
	home = ft_getenv(base->env, "HOME");
	if (home)
		home += 5;
	len = !home ? 0 : ft_strlen(home);
	while (len && *(home + len - 1) == '/')
		len--;
	if (len && !ft_strncmp(cwd, home, len))
	{
		tmp = ft_strdup(cwd + len - 1);		
		free(cwd);
		if (!tmp)
			ft_exit_minishell(base, -1);
		cwd = tmp;
		cwd[0] = '~';
	}
	ft_putstr(ANSI_COLOR_BLUE);
	ft_putstr(cwd);
    ft_putstr(ANSI_COLOR_RESET);
	free(cwd);
}

static void		ft_show_prompt_user(abs_struct *base)
{
	char		*str;
	size_t		len;

	str = ft_getenv(base->env, "USER");
	ft_putstr(ANSI_COLOR_GREEN);
	ft_putstr(str + 5);
	str = ft_getenv(base->env, "SESSION_MANAGER");
	if (str)
	{
		ft_putstr("@");
		len = ft_strchr(str, ':') - str - 16;
		ft_putnstr(str + 16, len);
	} 
	ft_putstr(ANSI_COLOR_RESET);
}

void    		ft_show_prompt(abs_struct *base)
{
	ft_show_prompt_user(base);
	ft_putstr(":");
	ft_show_prompt_cwd(base);
	ft_putstr("$ ");
}