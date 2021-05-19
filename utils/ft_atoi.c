/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:07:59 by vsempere          #+#    #+#             */
/*   Updated: 2021/04/01 16:01:44 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_sign(char **exit_code)
{
	while (**exit_code)
	{
		if (!ft_strchr("+-", **exit_code))
		{
			if (!ft_isdigit(**exit_code))
				return (0);
			break ;
		}
		(*exit_code)++;
	}
	return (1);
}

int	exists_non_digits_chars(char *exit_code)
{
	char	*trim;
	char	*tmp;

	trim = ft_trim(exit_code);
	if (!trim)
		return (0);
	tmp = trim;
	if (!check_sign(&tmp))
	{
		free(trim);
		return (1);
	}
	while (*tmp)
	{
		if (ft_isdigit(*tmp))
			tmp++;
		else
		{
			free(trim);
			return (1);
		}
	}
	free(trim);
	return (0);
}

static int	ft_get_sign(const char *nptr, size_t *i)
{
	int			sign;

	if (nptr[*i] == '-')
		sign = -1;
	else
		sign = 1;
	if (nptr[*i] == '-' || nptr[*i] == '+')
		(*i)++;
	return (sign);
}

int	ft_test_sign(int sign)
{
	if (sign < 0)
		return (0);
	return (-1);
}

int	ft_atoi(const char *nptr)
{
	long int	ret;
	long int	prv;
	size_t		i;
	int			sign;
	char		overflow;

	i = 0;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	sign = ft_get_sign(nptr, &i);
	overflow = 0;
	ret = 0;
	while (!overflow && ft_isdigit((int)nptr[i]))
	{
		prv = ret;
		ret = (ret + (nptr[i] - '0')) * 10;
		if (!(prv > ret))
			overflow = 0;
		i++;
	}
	if (!overflow)
		ret = (ret / 10) * sign;
	else
		ret = ft_test_sign(sign);
	return (ret);
}
