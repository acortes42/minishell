#include "minishell.h"

void	ft_print_last_process_status(t_expand_dollar *d)
{
	char			*expansion;
	char			*status;
	int				len;

	status = ft_itoa(d->base->error);
	if (!(status))
		ft_exit_minishell(1);
	len = ft_strlen(status);
	if (len > 2)
	{
		expansion = ft_calloc(d->expanded_len + (len - 2) + 2, sizeof(char));
		if (!(expansion))
			ft_exit_minishell(1);
		ft_memcpy(expansion, d->expanded, d->pos);
		ft_memcpy(expansion + d->pos, status, len);
		free(d->expanded);
		d->expanded = expansion;
		d->expanded_len += (len - 2);
	}
	else
		ft_memcpy(d->expanded + d->pos, status, len);
	d->pos += len;
	d->cmd += 2;
	free(status);
}
