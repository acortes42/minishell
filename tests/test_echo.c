#include "tests_minishell.h"

int				test_echo(void)
{
	int			res;
	t_abs_struct	abs;
	t_process	p;

	printf("--- Test echo\n");
	memset(&abs, 0, sizeof(t_abs_struct));
	abs.parse_string = calloc(3, sizeof(char *));
	abs.parse_string[0] = "echo";
	abs.parse_string[1] = "hola";
	ft_memset(&p, 0, sizeof(t_process));
	p.argv = abs.parse_string;
	res = echo(&abs, &p);
	free(abs.parse_string);
	printf("--- \n\n\n");
	return (res ? 0 : 1);
}