/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_history.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/01 16:07:21 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:07:26 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests_minishell.h"

int			test_history(void)
{
	printf("--- Test history\n");
	ft_history();
	printf("--- \n\n\n");
	return (0);
}