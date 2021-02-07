#include "minishell.h"

void    ft_show_prompt(abs_struct *base)
{
	(void)base;
    ft_putstr("\e[92m--->");
    // TODO: Mostrar directorio actual
}