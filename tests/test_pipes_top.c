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

void test(char **envp)
{
	pid_t	pid1;
	pid_t	pid2;
	//pid_t	pid3;
	int		fd[2];
	//int		fd23[2];
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
		close(fd[STDIN_FILENO]);
		dup2(fd[STDOUT_FILENO], STDOUT_FILENO);
		close(fd[STDOUT_FILENO]);
		char *argv[2];
		argv[0] = "grep";
		argv[1] = 0;
		// top
		execve("/bin/grep", argv, envp);
		int fd = open("./test_result", O_RDWR | O_CREAT | O_TRUNC, 0666);
		write(fd, strerror(errno), strlen(strerror(errno)));
		close(fd);
		exit(1);
	}

	//pipe(fd23);
	pid2 = fork();
	if (!pid2)
	{
		close(fd[STDOUT_FILENO]);
		dup2(fd[STDIN_FILENO], STDIN_FILENO);
		close(fd[STDIN_FILENO]);

		// close(fd23[STDIN_FILENO]);
		// dup2(fd23[STDOUT_FILENO], STDOUT_FILENO);
		// close(fd23[STDOUT_FILENO]);

		int status = wait_for_pid("Echo child", pid1);

		printf("top status %d %s\n",  status, strerror(errno));
		exit(0);
	}
	else
	{
		close(fd[STDIN_FILENO]);
		close(fd[STDOUT_FILENO]);

		printf("Top and echo launched (%d) (%d)\n", pid1, pid2);
		printf("Just waiting!!!!\n");
		wait_for_pid("Waiting por top", pid1);
		wait_for_pid("Waiting for echo", pid2);

		dup2(infile, STDIN_FILENO);
		dup2(outfile, STDOUT_FILENO);
		dup2(errfile, STDERR_FILENO);
		close(infile);
		close(outfile);
		close(errfile);
	}

	// pid3 = fork();
	// if (pid3)
	// {
	// 	close(fd[STDIN_FILENO]);
	// 	close(fd[STDOUT_FILENO]);
	// 	close(fd23[STDIN_FILENO]);
	// 	close(fd23[STDOUT_FILENO]);

	// 	printf("Top and echo launched (%d) (%d) (%d)\n", pid1, pid2, pid3);
	// 	printf("Just waiting!!!!\n");
	// 	wait_for_pid("Waiting por top", pid1);
	// 	wait_for_pid("Waiting for echo", pid2);
	// 	wait_for_pid("Waiting for ls", pid3);

	// 	dup2(infile, STDIN_FILENO);
	// 	dup2(outfile, STDOUT_FILENO);
	// 	dup2(errfile, STDERR_FILENO);
	// 	close(infile);
	// 	close(outfile);
	// 	close(errfile);
	// }
	// else
	// {
	// 	close(fd23[STDOUT_FILENO]);
	// 	dup2(fd23[STDIN_FILENO], STDIN_FILENO);
	// 	close(fd23[STDIN_FILENO]);

	// 	char *argv[2];
	// 	argv[0] = "ls";
	// 	argv[1] = 0;
	// 	// ls
	// 	execve("/bin/ls", argv, envp);
	// 	exit(1);
	// }

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
		close(fd[STDOUT_FILENO]);
		dup2(fd[STDIN_FILENO], STDOUT_FILENO);
		close(fd[STDIN_FILENO]);
		char *argv[2];
		argv[0] = "grep";
		argv[1] = 0;
		// top
		execve("/bin/grep", argv, envp);
		exit(1);
	}
	else
	{
		int status2 = wait_for_pid("Primera prueba", pid1);
		printf("Resultado primera prueba: %d\n", status2);
	}

	dup2(fd[STDOUT_FILENO], STDIN_FILENO);
	close(fd[STDIN_FILENO]);
	close(fd[STDOUT_FILENO]);

	int status = wait_for_pid("Echo child", pid1);

	printf("top status %d %s\n",  status, strerror(errno));

	printf("Top and echo launched (%d) \n", pid1);
	printf("Just waiting!!!!\n");
	wait_for_pid("Waiting por top", pid1);

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
