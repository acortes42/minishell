#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int arc, char **argv, char **envp)
{
	int		fd;
	char 	*params[2];
	int		len;
	char 	buffer[4096];
	(void)arc;
	(void)argv;

	params[0] = "/usr/local/test/d.sh";
	params[1] = 0;

	fd = open(params[0], O_RDONLY);
	if (fd >= 0)
		len = read(fd, buffer, 4096);
	buffer[len] = 0;
	printf("Read from file: %s\n", buffer);
	close(fd);

	printf("Executing...\n");
	execve("d.sh", params, envp);
	strerror(errno);

	return (0);
}
