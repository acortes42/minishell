#include "minishell.h"

void		clear_screen()
{
	ft_putstr("\e[0m\033[2J\033[1;1H");
	ft_putstr("\e[92m             |||------------------------------||| \n");
	ft_putstr("             |||------------------------------||| \n");
	ft_putstr("             |||------------------------------||| \n");
	ft_putstr("             |||           MINISHELL          ||| \n");
	ft_putstr("             |||------------------------------||| \e[0m\n\n\n");
}
