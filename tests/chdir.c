#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main(int arc, char **argv, char **envp)
{
	(void)arc;
	(void)argv;
	char *params[2];

	params[0] = "c.sh";
	params[1] = 0;
	printf("Executing...\n");
	execve("c.sh", params, envp);
	strerror(errno);
	return (0);
}
