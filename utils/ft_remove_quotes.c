/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_remove_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: visv <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 09:26:15 by visv              #+#    #+#             */
/*   Updated: 2021/03/14 09:26:16 by visv             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_remove_quotes(char *field)
{
	size_t			len;
	size_t			pos;
	
	len = ft_strlen(field);
	if (!len)
		return ;
	if ((*field != '"' || *(field + len - 1) != '"') &&
		(*field != '\'' || *(field + len - 1) != '\''))
		return ;
	pos = 1;
	while (*(field + pos) && pos < (len - 1))
	{
		*(field + pos - 1) = *(field + pos);
		pos++;
	}
	*(field + pos - 1) = *(field + len);
}
