/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 13:33:03 by acortes-          #+#    #+#             */
/*   Updated: 2021/01/23 16:28:03 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int obtain_full_line(abs_struct *base)
{
	char        c;
	int         fd;
	int         i;

	fd = open("history.txt", O_RDWR | O_APPEND);
	i = 0;
	while (read(0, &c, sizeof(char)) > 0)
	{
		write(fd, &c, 1);
		if (c == '\n')
			break;
		if (c != '\"' && c != '\'')
		{
			base->string[i] = c;
			i++;
		}
	}
	base->string[i] = '\0';
	close(fd);
	base->parseString = ft_split(base->string, ' ');
	return (0);
}

void clearScreen()
{
	ft_putstr("\e[0m\033[2J\033[1;1H");
	ft_putstr("\e[92m             |||------------------------------||| \n");
	ft_putstr("             |||------------------------------||| \n");
	ft_putstr("             |||------------------------------||| \n");
	ft_putstr("             |||           MINISHELL          ||| \n");
	ft_putstr("             |||------------------------------||| \e[0m\n\n\n");
}

int execute (abs_struct *base)
{   
	pid_t   pid;

// TODO: eliminar el valid_str? Creo que solo aporta confusion a la hora de entender los else if y puntos de error si no encajan los indices
	base->valid_str = ft_split("exit echo pwd cd history help env setenv unsetenv clear export", ' ');
	pid = fork();

	if (pid > 0)
		wait(&pid);
	else if (pid == 0)
	{
		base->num_args = 0;
		while (base->parseString[base->num_args])
			base->num_args++;
		base->actual_argument = 0;
		while (base->actual_argument <= base->num_args)
		{
			ft_putstr("\e[0m");
			if (ft_strcmp(base->string, base->valid_str[0]) == 0 ) 
				kill(pid, SIGINT);
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[1]) == 0)
				echo(base);
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[2]) == 0)
			{
				ft_pwd();
				base->error  = 0;
			}
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[3]) == 0)
			{    
				 cd(base);
				 base->actual_argument += 1;
			}
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[4]) == 0)
			{
				ft_history();
				base->error  = 0;
			}
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[5]) == 0)
				ft_help(base);
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[6]) == 0)
				ft_env(base);
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[7]) == 0)
				ft_setenv(base);
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[8]) == 0)
				ft_unsetenv(base);
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[9]) == 0)
				clearScreen();
			else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[10]) == 0)
				ft_export(base);
			else if ((base->parseString[base->actual_argument][0] == '.' && base->parseString[base->actual_argument][1] == '/')
					|| base->parseString[base->actual_argument][0] == '/')
				ft_launch(base);
			else
			{
				ft_putstr("Error en los argumentos\n");
				base->error = 1;
			}
			base->actual_argument++;

			// manejo de ; |
			if (!base->parseString[base->actual_argument])
				break ;
			else if (!ft_strcmp(base->parseString[base->actual_argument], ";"))
			{
				// Aquí creo que vuelve a ser necesaria la estructura que proponen en gnu o adaptar la que hay. El export ahora mismo no funciona 100%.
				base->actual_argument++;
			}
			else if (!ft_strcmp(base->parseString[base->actual_argument],  "|"))
			{
				// pensar en equipo como gestionar esto
				// Propuesta: Ver la estructura que proponen en la página de gnu.org para la implementación de un minishell. Y al realizar el analisis del comando, rellenar la estructura para luego comenzar a interpretar las redirecciones
				base->actual_argument++;
			}
			else
				break;
		}
    }
	else
		ft_putstr("\e[0mError en la creacion de subproceso\n");
	return (1);
}


int main(int argc, char **argv, char **envp)
{
	int         exceptionNum;
	abs_struct  *base;

	signal(SIGINT, handle_sigint);
	exceptionNum = 1;
	clearScreen();
	if (!(base = malloc(sizeof(abs_struct) * 1)))
	  	return (-1);
	ft_copy_env(base, envp);
	base->actual_argument = 0;
	base->flag = 0;
	base->error = 0;
	while (exceptionNum == 1)
	{
		ft_putstr("\e[92m--->");
		obtain_full_line(base);
		execute(base);         
	}
	// TODO: Release base struct
	(void)argc;
	(void)argv;
	return (0);
}