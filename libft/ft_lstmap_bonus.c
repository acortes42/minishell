/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:23:57 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/27 14:16:05 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew_st(void *content)
{
	t_list		*n;

	n = malloc(sizeof(t_list));
	if (n != 0)
	{
		n->content = (void *)content;
		n->next = 0;
	}
	return (n);
}

static void		ft_lstclear_st(t_list **lst, void (*del)(void *))
{
	t_list		*c;
	t_list		*n;

	c = *lst;
	n = c->next;
	while (c != 0)
	{
		del(c->content);
		c->content = 0;
		free(c);
		c = n;
		n = c ? c->next : 0;
	}
	lst = 0;
}

static void		ft_lstadd_back_st(t_list **alst, t_list *n)
{
	t_list		*last;

	last = (*alst);
	while (last != 0 && last->next != 0)
		last = last->next;
	if (last == 0)
		*alst = n;
	else
		last->next = n;
}

static int		ft_lstmap_node(t_list **r, t_list **itr, void (*del)(void *))
{
	int			added;
	t_list		*n;

	n = ft_lstnew_st(0);
	if (n == 0)
	{
		ft_lstclear_st(r, del);
		added = 0;
	}
	else
	{
		ft_lstadd_back_st(itr, n);
		*itr = n;
		added = 1;
	}
	return (added);
}

t_list			*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*r;
	t_list		*it;
	t_list		*itr;

	if (lst == 0)
		return (0);
	r = ft_lstnew_st(0);
	if (r == 0)
		return (0);
	itr = r;
	it = lst;
	while (it != 0)
	{
		itr->content = f(it->content);
		if (it->next == 0)
			it = it->next;
		else
		{
			if (ft_lstmap_node(&r, &itr, del))
				it = it->next;
			else
				it = 0;
		}
	}
	return (r);
}
