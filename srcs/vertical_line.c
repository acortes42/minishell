/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/08 14:06:46 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:05:03 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int vertical_line(t_abs_struct *base)
{
	//Do some work if necesary. This is the proposit of your existence.
	int silence_warnings;

	silence_warnings = base->actual_argument;
	ft_putstr("\e[0mEsta es una line vertical\n");
	return (silence_warnings);
}