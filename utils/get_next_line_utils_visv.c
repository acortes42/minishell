/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_visv.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 12:41:59 by vsempere          #+#    #+#             */
/*   Updated: 2021/05/01 16:27:19 by acortes-         ###   ########.fr       */
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
	*found_nl = 0;
	if (*(bf + b2c) == '\n')
		*found_nl = 1;
	line_len = ft_strlen(line);
	nl = malloc(sizeof(char) * (line_len + b2c + 1));
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

void	ft_shift_left_bytes(char *bf, int bytes)
{
	int				i;

	i = 0;
	while (bytes < BUFFER_SIZE)
	{
		*(bf + i) = *(bf + bytes);
		i++;
		bytes++;
	}
	*(bf + i) = 0;
}

void	ft_shift_left(char *bf)
{
	int				nl_pos;

	nl_pos = 0;
	while (nl_pos < BUFFER_SIZE && *(bf + nl_pos) && *(bf + nl_pos) != '\n')
		nl_pos++;
	if (nl_pos >= BUFFER_SIZE || !*(bf + nl_pos))
	{
		*bf = 0;
		return ;
	}
	nl_pos++;
	ft_shift_left_bytes(bf, nl_pos);
}

void	ft_borrow_char(int x, char **line, char *bf)
{
	char	*aux;

	ft_memset(bf, 0, BUFFER_SIZE);
	if (x > 0)
	{
		ft_delete_chars(1);
		aux = malloc(sizeof(char) * x);
		ft_strlcpy(aux, *line, ft_strlen(*line));
		if (*line)
			free(*line);
		*line = aux;
	}
}
