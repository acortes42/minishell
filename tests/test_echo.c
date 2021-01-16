#include "tests_minishell.h"

int				test_echo(void)
{
	int			res;
	abs_struct	abs;

	printf("--- Test echo\n");
	memset(&abs, 0, sizeof(abs_struct));
	abs.parseString = calloc(3, sizeof(char *));
	abs.parseString[0] = "echo";
	abs.parseString[1] = "hola";
	res = echo(&abs);
	free(abs.parseString);
	printf("--- \n\n\n");
	return (res ? 0 : 1);
}