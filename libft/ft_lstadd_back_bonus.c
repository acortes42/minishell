/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:19:35 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:19:39 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstadd_back(t_list **alst, t_list *n)
{
	t_list	*last;

	last = (*alst);
	while (last != 0 && last->next != 0)
		last = last->next;
	if (last == 0)
		*alst = n;
	else
		last->next = n;
}
