/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words_until_separator.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 15:42:47 by acortes-          #+#    #+#             */
/*   Updated: 2021/03/02 16:02:58 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count_words_until_separator(char **str, int actual_arg)
{
	int x;

	x = actual_arg;
	while (str[x])
	{
		if (ft_strcmp(str[x], "|") == 0 || ft_strcmp(str[x], ";") == 0 ||
			ft_strcmp(str[x], "<") == 0 || ft_strcmp(str[x], ">") == 0 ||
			ft_strcmp(str[x], ">>") == 0)
			return (x);
		x++;
	}
	return (x - actual_arg);
}
