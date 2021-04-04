/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:41:59 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:11:18 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_concat(char *line, char *bf, int *found_nl)
{
	int				i;
	int				b2c;
	int				line_len;
	char			*nl;

	b2c = 0;
	while (b2c < BUFFER_SIZE && *(bf + b2c) && *(bf + b2c) != '\n')
		b2c++;
	if (b2c < BUFFER_SIZE && *(bf + b2c) == '\n')
		*found_nl = 1;
	else
		*found_nl = 0;
	line_len = 0;
	while (*(line + line_len))
		line_len++;
	nl = malloc(sizeof(char) * (line_len +
		(b2c < BUFFER_SIZE ? b2c : BUFFER_SIZE) + 1));
	if (!nl)
		return (0);
	i = -1;
	while ((++i) < line_len)
		*(nl + i) = *(line + i);
	i = -1;
	while ((++i) < b2c && i < BUFFER_SIZE)
		*(nl + line_len + i) = *(bf + i);
	*(nl + line_len + i) = 0;
	return (nl);
}

void	ft_shift_left(char *bf)
{
	int				i;
	int				nl_pos;

	nl_pos = 0;
	while (nl_pos < BUFFER_SIZE && *(bf + nl_pos) && *(bf + nl_pos) != '\n')
		nl_pos++;
	if (nl_pos >= BUFFER_SIZE || !*(bf + nl_pos))
	{
		*bf = 0;
		return ;
	}
	i = 0;
	nl_pos++;
	while (nl_pos < BUFFER_SIZE)
	{
		*(bf + i) = *(bf + nl_pos);
		i++;
		nl_pos++;
	}
	*(bf + i) = 0;
}
