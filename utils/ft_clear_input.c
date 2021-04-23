#include "minishell.h"

void	ft_clear_input(int chars)
{
	char			*str;
	struct termios	settings;

	if (tcgetattr (STDIN_FILENO, &settings) < 0)
		return ;
	str = ft_calloc((chars * 3) + 1, sizeof(char));
	if (!str)
		return ;
	ft_memset(str, settings.c_cc[VERASE], chars);
	ft_memset(str + chars, ' ', chars);
	ft_memset(str + chars + chars, settings.c_cc[VERASE], chars);
	ft_putstr(str);
	free(str);
}
