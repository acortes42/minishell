/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_add.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:03:05 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_array_delete_pos(char ***array, int *array_len, int pos)
{
	char	**array_dup;

	if (!array || !(*array))
		return (0);
	array_dup = ft_array_dup_without(*array, *array_len, *(*array + pos));
	free(*(*array + pos));
	free(*array);
	*array = array_dup;
	(*array_len)--;
	return (1);
}

int	ft_array_add(char ***array, int *array_len, char *value)
{
	char		**aux;
	int			x;

	x = 0;
	aux = malloc(sizeof(char *) * (*array_len + 2));
	if (!(aux))
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
