#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	int	status;

	printf("%s: waiting for child %d\n", message, pid);
	res = 0;
	while (!res)
	{
		res = waitpid(pid, &status, WNOHANG);
		if (res && WIFEXITED(status))
			status = WEXITSTATUS(status) % 256;
	}
	printf("%s: Child %d exit status %d\n", message, pid, status);
	return (status);
}

int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;
	pid_t	pid1;
	pid_t	pid2;
	int		fd[2];

signal(SIGINT, signals);
		pipe(fd);
		pid1 = fork();
		if (!pid1)
		{
			close(fd[STDIN_FILENO]);
			dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
			close(fd[STDOUT_FILENO]);
			char *argv[2];
			argv[0] = "top";
			argv[1] = 0;
			// top
			printf("Top thread child\n");
			execve("/usr/bin/top", argv, envp);
			exit(1);
		}

		pid2 = fork();
		if (pid2)
		{
			close(fd[STDIN_FILENO]);
			close(fd[STDOUT_FILENO]);
			printf("Top and echo launched (%d) (%d)\n", pid1, pid2);
			printf("Just waiting!!!!\n");
			wait_for_pid("Waiting por top", pid1);
			wait_for_pid("Waiting for echo", pid2);
		}
		else
		{
			close(fd[STDOUT_FILENO]);
			dup2(fd[STDIN_FILENO], STDIN_FILENO);
			close(fd[STDIN_FILENO]);
			int status = wait_for_pid("Echo child", pid1);
			printf("top status %d\n",  status);
			exit(0);
		}

}
