/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_minishell.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 15:54:14 by visv              #+#    #+#             */
/*   Updated: 2021/04/21 14:45:27 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void ft_init_history(t_abs_struct *base)
{
	int		fd;

	fd = ft_open_history(base, O_RDONLY);
	base->history_lines = ft_file_lines_by_fd(fd);
	close(fd);
	if (base->history_lines < 0)
		ft_exit_minishell(base, -1);
	base->current_history_line = base->history_lines + 1;
	// La idea es cargar el número de líneas y apuntar a la última línea. Después con una función de apoyo permitir solicitar la línea que queremos del archivo de modo que nos abstraemos de toda la lógica y sólo llamamos a la función
	// En el procesamiento del teclado, actualizamos el puntero a la línea del history, no dejando superar el índice máximo o mínimo.
	// Si se rebasa por arriba, borramos todo y queda apuntando al history + 1
	// Si se rebasa por abajo, no permitimos que se rebase y quedamos mostrando la primera línea del fichero history
	// Estos flags de los que hablo, serían los 2 flags siguientes:
	// El valor base->history_lines se carga a partir de leer el contenido del history
	// El valor base->current_history_line debe actualizarse cuando se pulsan las flechas, sin dejar bajar del 1 o pasar del base->history_lines
	//
	// No me da tiempo a mas. Vi lo que has implementado. Dejé algunos comentarios porque vi cosas que creo que no podemos entregar así, además vi algunos leaks y dejé una base por donde creo que puede complementar lo que tienes planteado y que puede que te ayude mañana.
	// He generado 3 ficheros nuevos:
	// - ft_open_history -> obtiene el fd del history o -1 en caso de error
	// - ft_file_lines -> dado un path nos devuelve el número de filas del archivo (leyendo caracter a caracter... por simplificar)
	// - ft_get_file_line -> nos da la línea que indicamos del archivo que pedimos
	//
	//
	// Creo que necesitamos cuidar los nombres de las variables, .., para mantener la legibilidad (no se si piensas lo mismo), por ejemplo vi una variable que se llama a, dentro de la estructura y me tocó pelearme con el historial de git para entender de dónde venía
	// Yo soy el primero que se lía con los nombres y que no lo hace claro, pero creo que tenemos que levantar los dos la mano cuando vemos esto.
}

int	ft_init_minishell(t_abs_struct *base, char **envp)
{
/* 	int	fd2;
	char	*buf_line;
 */
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);
	signal(SIGTTIN, SIG_IGN);
	signal(SIGTTOU, SIG_IGN);
	if (!base)
		return (0);
	ft_memset(base, 0, sizeof(t_abs_struct));
	ft_copy_env(base, envp);
	ft_init_history(base);
/* 	if (!(base->last_line)) // Siempre va a ser 0. Creo que no tiene sentido el if
	{
		// TODO: Cambiar todos estos open por ft_open_history (tiene fuga de memoria y apuntamos a un env fijo que no tiene porque tener lo que esperamos)
		// TODO: Comentado porque explota cuando no encuentra el fichero history porque buf_line es nulo y lo intenamos liberar al final del if
		// Creo que no debemos cargar la last line, sino utilizar el métofo ft_get_file_line a partir del valor de base->current_history_line .
		// Ver comentarios del ft_init_history
		fd2 = ft_open_history(base, O_RDONLY);
		buf_line = 0;
		base->last_line = ft_obtain_last(fd2, &buf_line);
		if (fd2)
			close(fd2);
		if (buf_line);
			free(buf_line);
	}
 */
	base->counter = 0;
	return (1);
}
