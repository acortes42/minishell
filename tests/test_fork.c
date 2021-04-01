/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:07:30 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:12:52 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests_minishell.h"

int main(void)
{
	int pid;
	int result;

	pid = fork();
	if (!pid)
	{
		char **argv;
		argv = calloc(3, sizeof(char *));
		argv[0] = calloc(4, sizeof(char));
		argv[1] = calloc(3, sizeof(char));
		memcpy(argv[0], "/bin/cat", 9);
		memcpy(argv[1], "ss", 2);
		execve(argv[0], argv, 0);
		exit(0);
	}
	result = 0;
	wait(&result);
	printf("%d result\n", result);
}