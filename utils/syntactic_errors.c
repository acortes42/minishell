#include "minishell.h"

static int	found_consecutive_chars(char *cmd, int car, int num_occurs)
{
	int		occurs;

	occurs = 0;
	while (cmd && *cmd)
	{
		if (*cmd == car)
			occurs++;
		else if (!ft_isspace(*cmd))
			occurs = 0;
		if (occurs >= num_occurs)
			return (1);
		cmd++;
	}
	return (0);
}

int	check_base_syntatic_errors(char *cmd)
{
	int		ret;
	char	*cmd_trim;

	if (!cmd)
		return (0);
	cmd_trim = ft_trim(cmd);
	if (!cmd_trim)
		return (0);
	if (!ft_strcmp(cmd_trim, ";") || !ft_strcmp(cmd_trim, "|")
		|| !ft_strcmp(cmd_trim, "||") || found_consecutive_chars(cmd, ';', 2)
		|| found_consecutive_chars(cmd, '|', 3) || ft_strstr(cmd_trim, "2>>"))
		ret = 258;
	else
		ret = 0;
	free(cmd_trim);
	return (ret);
}
