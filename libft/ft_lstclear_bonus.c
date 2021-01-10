/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:21:22 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:18:18 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_lstdelone_st(t_list *lst, void (*del)(void *))
{
	del(lst->content);
	lst->content = 0;
}

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*c;
	t_list	*n;

	c = *lst;
	n = c->next;
	while (c != 0)
	{
		ft_lstdelone_st(c, del);
		free(c);
		c = n;
		n = c ? c->next : 0;
	}
	*lst = 0;
}
