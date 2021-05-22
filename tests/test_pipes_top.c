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

	res = 0;
	while (!res)
	{
		res = waitpid(pid, &status, WNOHANG | WUNTRACED);
		if (res > 0)
		{
			if (WIFEXITED(status))
				status = WEXITSTATUS(status) % 256;
			else if (WIFSIGNALED(status))
				status = 128 + WTERMSIG(status);
			else if (WIFSTOPPED(status))
				status = 0;
			else
				status = 0;
		}
	}
	return (status);
}

void test(char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	pid_t	pid3;
	int		fd[2];
	int		fd23[2];
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
		write(STDERR_FILENO, "CAT\n", 4);
		close(fd[STDIN_FILENO]);
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		close(fd[STDOUT_FILENO]);
		char *argv[3];
		argv[0] = "cat";
		argv[1] = "author";
		argv[2] = 0;
		// top
		execve("/bin/cat", argv, envp);
		write(STDERR_FILENO, "*CAT\n", 5);
		exit(111);
	}

	pipe(fd23);
	pid2 = fork();
	if (!pid2)
	{
		write(STDERR_FILENO, "SORT\n", 5);

		close(fd[STDOUT_FILENO]);
		dup2(fd[STDIN_FILENO], STDIN_FILENO);
		close(fd[STDIN_FILENO]);

		close(fd23[STDIN_FILENO]);
		dup2(fd23[STDOUT_FILENO], STDOUT_FILENO);
		close(fd23[STDOUT_FILENO]);

		char *argv[2];
		argv[0] = "sort";
		argv[1] = 0;
		execve("/usr/bin/sort", argv, envp);
		write(STDERR_FILENO, "*SORT\n", 6);
		exit(112);
	}

	pid3 = fork();
	if (!pid3)
	{
		write(STDERR_FILENO, "MORE\n", 5);
		close(fd[STDIN_FILENO]);
		close(fd[STDOUT_FILENO]);
		dup2(fd23[STDIN_FILENO], STDIN_FILENO);
		close(fd23[STDIN_FILENO]);
		close(fd23[STDOUT_FILENO]);

		char *argv[2];
		argv[0] = "more";
		argv[1] = 0;
		execve("/bin/more", argv, envp);
		write(STDERR_FILENO, "*MORE\n", 6);
		exit(113);
	}
	else
	{
		write(STDERR_FILENO, "Esperando a todos\n", strlen("Esperando a todos\n"));

		close(fd[STDIN_FILENO]);
		close(fd[STDOUT_FILENO]);
		close(fd23[STDIN_FILENO]);
		close(fd23[STDOUT_FILENO]);

		wait_for_pid("wait cat", pid1);
		wait_for_pid("wait sort", pid2);
		wait_for_pid("wait more", pid3);

		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		dup2(errfile, STDERR_FILENO);
		close(infile);
		close(outfile);
		close(errfile);
	}

}



int main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	test(envp);
}
