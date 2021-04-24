#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <string.h>

int main(void)
{
	struct termios	sets;
	char			bf[4];
	size_t			bytes;
	int				end;
	tcflag_t		lflag;
	char			c;
	char			d;

	tcgetattr(STDIN_FILENO, &sets);
	lflag = sets.c_lflag ;
	sets.c_lflag |= ICANON;
	tcsetattr(STDIN_FILENO, TCSANOW, &sets);

		write(STDOUT_FILENO, "HOLA", 4);
		write(STDOUT_FILENO, "\b", 1);
		write(STDOUT_FILENO, "J", 1);

/* 	d = 8;
	c = 127;
	end = 0;
	while (!end) {
		bytes = read(STDIN_FILENO, bf, 4);
		write(STDOUT_FILENO, "HOLA", 4);
		write(STDOUT_FILENO, bf, bytes);
		write(STDOUT_FILENO, "\b", 1);
		write(STDOUT_FILENO, "\b", 1);
		write(STDOUT_FILENO, "\b", 1);
		write(STDOUT_FILENO, "J", 1);

		end = bf[0] == 'z';
	}
 */
	sets.c_lflag  = lflag;
	tcsetattr(STDIN_FILENO, TCSANOW, &sets);
}
