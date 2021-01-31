#include "tests_minishell.h"

static void		print_test_result(const char *test, int res)
{
	const char	*res_str;

	if (!res)
		res_str = "OK";
	else
		res_str = "Failed";
	printf("%50s : %s\n", test, res_str);
}

int				main(int argc, char **argv, char **env)
{
    (void)argc;
    (void)argv;
    (void)env;
	int			res;

	// Tests
	res = test_history();
	print_test_result("History", test_history());
	if (res)
		return (res);
	res = test_echo();
	print_test_result("echo", test_echo());
	return (res);
}