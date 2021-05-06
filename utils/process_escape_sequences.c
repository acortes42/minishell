#include "minishell.h"

static int	process_control_characters(char *bf, char **line)
{
	if (!bf)
		return (0);
	if (*bf == CTRL_C)
	{
		ft_clear_input(line);
		ft_putstr("\n");
		ft_memset(bf, 0, BUFFER_SIZE);
		return (1);
	}
	else if (*bf == DEL)
	{
		ft_borrow_char(ft_strlen(*line), line, bf);
		ft_memset(bf, 0, BUFFER_SIZE);
		return (1);
	}
	else if (*bf <= 0x6)
	{
		ft_memset(bf, 0, BUFFER_SIZE);
		return (1);
	}
	return (0);
}

static int	process_fe_escape_sequence(char *bf)
{
	if (!bf || *bf != ESCAPE || !(*(bf + 1)))
		return (0);
	if (*(bf + 1) >= FE_ESCAPE_START && *(bf + 1) <= FE_ESCAPE_END
		&& ft_strncmp(bf, CSI_ESCAPE, 2))
	{
		bf[0] = 0;
		bf[1] = 0;
		return (1);
	}
	return (0);
}

int	process_escape_sequences(char *bf, char **line, t_abs_struct *base)
{
	if (process_fe_escape_sequence(bf))
		return (1);
	if (process_csi_escape_sequence(bf, line, base))
		return (1);
	if (process_control_characters(bf, line))
		return (1);
	return (0);
}
