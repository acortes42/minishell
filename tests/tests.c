/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:04:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:07:12 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests_minishell.h"

static void	print_test_result(const char *test, int res)
{
	const char	*res_str;

	if (!res)
		res_str = "OK";
	else
		res_str = "Failed";
	printf("%50s : %s\n", test, res_str);
}

int	main(int argc, char **argv, char **env)
{
	int	res;

	(void)argc;
	(void)argv;
	(void)env;
	res = test_history();
	print_test_result("History", test_history());
	if (res)
		return (res);
	res = test_echo();
	print_test_result("echo", test_echo());
	return (res);
}
