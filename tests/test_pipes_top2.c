#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char **argvp, char **envp)
{
	(void) argc;
	(void) argvp;
	char	*argv[2];
	pid_t	pid1;
	int		fd[2];
	int		top_status;
	int		infile;
	int		outfile;

	infile = dup(STDIN_FILENO);
	outfile = dup(STDOUT_FILENO);

	pipe(fd);

	pid1 = fork();
	if (!pid1)
	{
		close(fd[STDIN_FILENO]);
		if (dup2(fd[STDOUT_FILENO], STDOUT_FILENO) < 0)
			printf("Error child: %s\n", strerror(errno));
		argv[0] = "top";
		argv[1] = 0;
		write(STDERR_FILENO, "Launching top\n", strlen("Launching top\n"));
		execve("/usr/bin/top", argv, envp);
		exit(1);
	}

	waitpid(pid1, &status, 0);
		if (WIFEXITED(status))
			printf("Estado top %d\n", WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("Top signaled %d\n", WTERMSIG(status));
		else if (WIFSTOPPED(status))
			printf("Stop signal %d\n", WSTOPSIG(status));
		else
		{
			printf("Error esperando estado top\n");
		}

		exit(0);
	}

	printf("Waiting for top (%d)\n", pid1);
	waitpid(pid2, &top_status, 0);
	printf("Top status %d %s\n", WEXITSTATUS(top_status), strerror(errno));
	dup2(infile, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
	close(infile);
	close(outfile);
	return (0);
}
