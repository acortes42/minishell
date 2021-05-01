/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_file_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/01 16:57:10 by acortes-          #+#    #+#             */
/*   Updated: 2021/05/01 16:57:11 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_file_line_by_fd(int fd, int line)
{
	char	*str;
	int		curr_line;
	int		found_nl;

	if (fd < 0)
		return (0);
	curr_line = 0;
	str = 0;
	while (curr_line <= line)
	{
		// TODO: Corregir el otro gran problema que tenemos aquí...
		// Como abrimos y cerramos el fichero sin leerlo del todo  al leer el history, lo que leemos la próxima vez, no es lo que esperamos sino el buffer que quedó pendiente de leer hasta el final del archivo
		// Bastaría con implementar un close que limpie el buffer del fd, con esto el subir y bajar por el historial va medianamente fino

		found_nl = classic_get_next(fd, &str);
		//close(fd);
		if (found_nl < 1)
			break ;
		if (str && curr_line < line)
		{
			free(str);
			str = 0;
		}
		curr_line++;
	}
	if (curr_line < line && str)
	{
		free(str);
		str = 0;
	}
	return (str);
}

char	*ft_get_file_line(char *file, int line)
{
	char	*str;
	int		fd;

	if (!file || line < 0)
		return (0);
	fd = open(file, O_RDONLY);
	str = ft_get_file_line_by_fd(fd, line);
	close(fd);
	return (str);
}
