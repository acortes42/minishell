/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_csi_sequences.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/15 18:04:35 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_csi_escape_sequence_complete(char *bf)
{
	char		*tmp;

	if (ft_strncmp(bf, CSI_ESCAPE, 2))
		return (0);
	tmp = bf + 2;
	while (*tmp >= 0x30 && *tmp <= 0x3F)
		tmp++;
	while (*tmp >= 0x20 && *tmp <= 0x2F)
		tmp++;
	if (*tmp >= 0x40 && *tmp <= 0x7E)
		return (1);
	return (0);
}

static void	read_csi_escape_sequence(char *bf)
{
	int		len;

	len = ft_strlen(bf);
	while (bf && len < BUFFER_SIZE)
	{
		read(STDIN_FILENO, bf + len, 1);
		if (*(bf + len) >= 0x40 && *(bf + len) <= 0x7E)
			break ;
		len++;
	}
}

int	process_csi_escape_sequence(char *bf, char **line, t_abs_struct *base)
{
	base->counter = 0;
	if (ft_strncmp(bf, CSI_ESCAPE, 2))
		return (0);
	if (!is_csi_escape_sequence_complete(bf))
		read_csi_escape_sequence(bf);
	if (bf[2] == base->arrow_up[2])
		load_previous_history_command(base, line, bf);
	else if (bf[2] == base->arrow_down[2])
		load_next_history_command(base, line, bf);
	else
		ft_memset(bf, 0, BUFFER_SIZE);
	return (1);
}
