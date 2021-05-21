#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void signals(int signal)
{
	printf("Signal %d\n", signal);
}

int wait_for_pid(char *message, pid_t pid)
{
	pid_t res;
	int	status = -1;

	printf("%s: waiting for child %d\n", message, pid);
	res = 0;
	while (!res)
	{
		res = waitpid(pid, &status, WNOHANG);
		if (res > 0 && WIFEXITED(status))
			status = WEXITSTATUS(status) % 256;
		else if (res < 0) {
			status = -2;
			printf("Waitpid error %s for pid %d\n", strerror(errno), pid);
		}
	}
	printf("%s: Child %d exit status %d (%s)\n", message, pid, status, strerror(errno));
	return (status);
}


int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;

		char *argv2[2];
		argv2[0] = "grep";
		argv2[1] = 0;
		// top
		execve("/bin/grep", argv2, envp);
}
