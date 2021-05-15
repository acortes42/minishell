#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>

void	forked_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("Forked\n");
		exit(128 + signal);
	}
}

void	main_signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		printf("Main\n");
	}
}

// Test to understand how signals works
// Initially written because minishell didn't catch expected signal_handler during execve executions
// The explanation is foun in : man 7 signal. And basically it's that execve will reset signal handlers to parent ones so any signal_handler set in forked process will be reset
int main(void)
{
	pid_t forked;

	signal(SIGINT, main_signal_handler);
	forked = fork();
	if (!forked)
	{
		//signal(SIGINT, forked_signal_handler);
		printf("Chiild alive!\n");
		pause();
		printf("Child almost done\n");
		exit(0);
	}

	printf("Main process will sleep for a while\n");
	sleep(3);
	printf("Killing child process %d\n", forked);
	kill(forked, SIGINT);
	pause();
	printf("Main process almost done\n");
	exit(0);
}
