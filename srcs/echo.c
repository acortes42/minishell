#include "../minishell.h"

int echo(abs_struct *base)
{
    int i;

    i = 1;
    while (base->parseString[i])
    {
        if (ft_strcmp(base->parseString[i], "|") != 0 && ft_strcmp(base->parseString[i], ";") != 0)
        {
            ft_putstr(base->parseString[i]);
            i++;
            base->actual_argument++;
        }
        else
        {
            if (ft_strcmp(base->parseString[i], "|") != 0 )
            base->flag = 1;
            break;
        }
    }
    ft_putstr("\n");
    return (1);
}