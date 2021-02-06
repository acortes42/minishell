/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsempere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 14:15:08 by vsempere          #+#    #+#             */
/*   Updated: 2019/11/17 14:15:13 by vsempere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			*ft_calloc(size_t nmemb, size_t size)
{
	void		*r;

	r = malloc(nmemb * size);
	if (r != 0)
		ft_bzero(r, (nmemb * size));
	return (r);
}
