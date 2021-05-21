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
			status = -69;
			printf("Waitpid error %s for pid %d\n", strerror(errno), pid);
		}
	}
	printf("%s: Child %d exit status %d (%s)\n", message, pid, status, strerror(errno));
	return (status);
}

void test2(char **envp)
{
	pid_t	pid1;
	int		fd[2];
	int		infile;
	int		outfile;
	int		errfile;

	infile = dup(STDIN_FILENO);
	outfile = dup(STDOUT_FILENO);
	errfile = dup(STDERR_FILENO);

	signal(SIGINT, signals);

	pipe(fd);
	pid1 = fork();
	if (!pid1)
	{
		printf("Top thread child\n");
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		close(fd[STDIN_FILENO]);
		close(fd[STDOUT_FILENO]);
		char *argv[2];
		argv[0] = "top";
		argv[1] = 0;
		// top
		execve("/bin/top", argv, envp);
		exit(1);
	}

	dup2(fd[STDIN_FILENO], STDIN_FILENO);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);

	printf("Waiting for top (%d)\n", pid1);
	int status = wait_for_pid("Echo child", pid1);

	printf("Top status %d %s\n",  status, strerror(errno));

	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	dup2(errfile, STDERR_FILENO);
	close(infile);
	close(outfile);
	close(errfile);


}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	test2(envp);
}
