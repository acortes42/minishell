#include "minishell.h"

void	ft_expand_quote(t_expand_dollar *d)
{
	if (!d->quote)
		d->quote = '"';
	else
		d->quote = 0;
	d->cmd++;
}

void	ft_expand_tilde(t_expand_dollar *d)
{
	char	*tilde_path;
	char	*tmp;

	tilde_path = ft_get_absolute_path(d->base, "~");
	if (!tilde_path)
		return ;
	tmp = ft_calloc(d->expanded_len + ft_strlen(tilde_path) + 2, sizeof(char));
	if (!tmp)
	{
		free(tilde_path);
		return ;
	}
	ft_memcpy(tmp, d->expanded, d->pos);
	ft_memcpy(tmp + d->pos, tilde_path, ft_strlen(tilde_path));
	if (d->expanded)
		free(d->expanded);
	d->expanded = tmp;
	d->pos += ft_strlen(d->expanded);
	d->expanded_len += ft_strlen(tilde_path) - 1;
	free(tilde_path);
}
