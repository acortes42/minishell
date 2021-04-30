/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setlflag.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acortes- <acortes-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 18:49:03 by visv              #+#    #+#             */
/*   Updated: 2021/04/30 15:27:28 by acortes-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void enableRawMode() 
{
  struct termios raw;

  raw.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  raw.c_oflag &= ~(OPOST);
  raw.c_cflag |= (CS8);
  raw.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  raw.c_cc[VMIN] = 0;
  raw.c_cc[VTIME] = 1;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
*/
int	ft_setlflag(int fd, int set_flag, unsigned int value)
{
	struct termios	settings;
	int				result;

	result = tcgetattr (fd, &settings);
	if (result < 0)
	{
		perror ("error in tcgetattr");
		return 0;
	}
	settings.c_lflag &= ~value;
	if (set_flag)
		settings.c_lflag |= value;

	result = tcsetattr (fd, TCSANOW, &settings);
	if (result < 0)
	{
		perror ("error in tcsetattr");
		return (0);
	}
	return (1);
}
