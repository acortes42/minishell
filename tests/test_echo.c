/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:12:34 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/15 15:00:03 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	res = ft_echo(&abs, &p);
	free(abs.parse_string);
	printf("--- \n\n\n");
	return (res ? 0 : 1);
}