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
		else if (ft_strcmp(base->string, base->valid_str[0]) == 0 )
			ft_exit_minishell(base);
		else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[1]) == 0)
			echo(base);
		else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[2]) == 0)
		{
			ft_pwd();
			base->error  = 0;
		}
		else if (ft_strcmp(base->parseString[base->actual_argument], base->valid_str[3]) == 0)
			cd(base);
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
	return (base->error);
}