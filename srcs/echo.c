/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:27 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/15 14:59:51 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	echo_args(char **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		ft_putstr(argv[i]);
		i++;
		if (argv[i])
			ft_putstr(" ");
	}
}

static void	parse_n_flag(char ***args, int *active)
{
	if (!args)
		return ;
	*active = 0;
	while (*args)
	{
		*args = get_first_non_empty_arg_pos(*args);
		if (!(*args))
			return ;
		else
		{
			if (ft_strcmp(**args, "-n"))
				return ;
			else
			{
				*active = 1;
				(*args) ++;
			}
		}
	}
}

int	ft_echo(t_process *p)
{
	int		i;
	int		flag;
	char	**args;

	i = 1;
	if (!p->argv[i])
	{
		ft_putstr("\n");
		return (1);
	}
	flag = 0;
	args = p->argv + 1;
	parse_n_flag(&args, &flag);
	if (!args)
	{
		if (!flag)
			ft_putstr("\n");
		return (1);
	}
	echo_args(args);
	if (!flag)
		ft_putstr("\n");
	return (1);
}
