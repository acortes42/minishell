#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

void	process_signal(int signal)
{
	printf("Signal %d\n", signal);
}

int main(void)
{
	struct termios _termios;
	char c[1];

	signal(3, process_signal);
	tcgetattr(STDIN_FILENO, &_termios);
	printf("quit\n");
	*c = _termios.c_cc[VQUIT];
	write(STDOUT_FILENO, c, 1);
	printf("\nquitted\n");
	sleep(100);
}
