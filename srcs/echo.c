#include "../minishell.h"

int echo(abs_struct *base)
{
    int x;

    x = 4;

    while (base->string[x] == ' ' || base->string[x] == 9)
        x++;
    ft_printf("%s\n", base->string + x);
    return (1);
}