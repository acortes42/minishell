/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_update.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/04/01 16:03:05 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	release_array(char **array)
{
	if (array)
		free(array);
	return (0);
}

int	ft_array_update(char ***array, int *array_len, char *key, char *value)
{
	char	**updated_array;
	char	*tmp;

	tmp = ft_getenv(*array, key);
	if (!tmp)
		return (0);
	updated_array = ft_array_dup_without(*array, *array_len, tmp);
	if (!updated_array)
		return (0);
	(*array_len)--;
	free(tmp);
	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (release_array(updated_array));
	key = ft_strjoin(tmp, value);
	free(tmp);
	if (!key)
		return (release_array(updated_array));
	free(*array);
	*array = updated_array;
	return (ft_array_add(array, array_len, key));
}
