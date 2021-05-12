#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>


static void		redirection_input(char **env)
{
	char *argv[2];
	int	fd;
	int pipes[2];
	char buf[4096];
	int bytes;

	fd = open("/home/visv/42/code/minishell_adrian/minishell/author", O_RDONLY);
	bytes = read(fd, buf, 4096);
	write(STDIN_FILENO, buf, bytes);
	close(fd);
	/* if (dup2(fd, pipes[STDIN_FILENO]) == -1)
	{
		printf("Error abriendo archivo %s\n", strerror(errno));
		exit(0);
	 }*/
	argv[0] = "cat";
	argv[1] = 0;
	execve(*argv, argv, env);
}

int main(int argc, char **argv, char **env)
{
	(void)argv;
	(void)argc;
	redirection_input(env);
	return (0);
}
