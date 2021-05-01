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
	if (b2c < BUFFER_SIZE && *(bf + b2c) == '\n')
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

static void	delete_char(char *bf)
{
	ft_delete_chars(1);
	ft_memset(bf, 0, BUFFER_SIZE);
}

void	ft_borrow_char(int x, char **line, char *bf)
{
	char	*aux;

	if (x > 0)
	{
		aux = malloc(sizeof(char) * x);
		ft_strlcpy(aux, *line, ft_strlen(*line));
		delete_char(bf);
		ft_memset(bf, 0, BUFFER_SIZE);
		*line = ft_strdup(aux);
		free(aux);
	}
	else
	{
		ft_putstr(" ");
		*line = ft_strdup("");
	}
}
