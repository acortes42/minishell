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

void    		ft_show_prompt(abs_struct *base)
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
	ft_putstr("\e[92m");
	ft_putstr(cwd);
    ft_putstr("$");
	free(cwd);
}