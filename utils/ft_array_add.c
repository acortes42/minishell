/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:04:45 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_array_add(char ***array, int *array_len, char *value)
{
    char		**aux;
    int			x;

    x = 0;
    if (!(aux = malloc(sizeof(char *) * (*array_len + 2))))
		return (0);
    while (x < *array_len)
    {
        *(aux + x) = *((*array) + x);
		*((*array) + x) = 0;
        x++;
    }
    *(aux + x) = value;
	(*array_len)++;
	aux[*array_len] = NULL;
	if (*array)
		free(*array);
	*array = aux;
    return (1);
}
