#include "minishell.h"

int				ft_execute_command(abs_struct *base)
{
	base->num_args = 0;
	while (base->parseString[base->num_args])
		base->num_args++;
	base->actual_argument = 0;
	while (base->actual_argument <= base->num_args)
	{
		ft_putstr("\e[0m");
		if (!base->string || !*base->string)
		{
			ft_execute_ctrl_d(base);
			break ;
		}
		else if (!ft_strcmp(base->string, "exit"))
			ft_exit_minishell(base, 0);
		else if (!ft_strcmp(base->parseString[base->actual_argument], "echo"))
			echo(base);
		else if (!ft_strcmp(base->parseString[base->actual_argument], "pwd"))
		{
			ft_pwd();
			base->error  = 0;
		}
		else if (!ft_strcmp(base->parseString[base->actual_argument], "cd"))
			cd(base);
		else if (!ft_strcmp(base->parseString[base->actual_argument], "history"))
		{
			ft_history();
			base->error  = 0;
		}
		else if (!ft_strcmp(base->parseString[base->actual_argument], "help"))
			ft_help(base);
		else if (!ft_strcmp(base->parseString[base->actual_argument], "env"))
			ft_env(base);
		else if (!ft_strcmp(base->parseString[base->actual_argument], "setenv"))
			ft_setenv(base);
		else if (!ft_strcmp(base->parseString[base->actual_argument], "unsetenv"))
			ft_unsetenv(base);
		else if (!ft_strcmp(base->parseString[base->actual_argument], "clear"))
			clearScreen();
		else if (!ft_strcmp(base->parseString[base->actual_argument], "export"))
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
	return (base->error);
}