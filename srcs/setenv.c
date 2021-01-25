/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 16:04:45 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:04:45 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO: modificar el nombre de fichero por ft_setenv.c
// Problema al solo aceptar dos introducciones con setenv

/*Existe un problema al crear al crear más memoria y copiar lo necesario*/

static int		ft_add_line(char ***envp, int *elems, char *env_value)
{
    char		**aux;
    int			x;

	if (!env_value || !ft_strchr(env_value, '='))
		return (1);
    x = 0;
    if (!(aux = malloc(sizeof(char *) * (*elems + 2))))
		return (0);
    while (x < *elems)
    {
        *(aux + x) = *((*envp) + x);
		*((*envp) + x) = 0;
        x++;
    }
    *(aux + x) = ft_strdup(env_value);
	(*elems)++;
	aux[*elems] = NULL;
	if (*envp)
		free(*envp);
	*envp = aux;
    return (1);
}


static int	ft_search_env(char **env, char *key)
{
	int		pos;
	char	**tmp;
	size_t	key_len;

	key_len = ft_strlen(key);
	pos = 0;
	tmp = env;
    while (key_len && tmp && *tmp)
    {
		if (ft_strlen(*tmp) > key_len && 
			!ft_memcmp(*tmp, key, key_len) && *((*tmp) + key_len) == '=')
             return (pos);
        tmp++;
		pos++;
    }
    return (0);
}

int			ft_setenv(abs_struct *base)
{
	int		ret;
	char	**key_value;

	key_value = ft_split(base->parseString[base->actual_argument + 1], '=');
    if (key_value)
    {
        if (ft_search_env(base->env, key_value[0]))
			ft_unsetenv(base);
		if (!(ret = ft_add_line(&base->env, &base->lines_envp,
			base->parseString[base->actual_argument + 1])))
		    ft_putstr("\e[0mNo se añadió el argumento\n");
		ft_array_release(key_value);
		return (ret);
    }
    ft_putstr("\e[0mError en los argumentos\n");
	base->error = 0;
    return (0);
}