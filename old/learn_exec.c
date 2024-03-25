#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == -1)
	{
		perror("fork error\n");
		return (1);
	}
	if (pid == 0)
	{
		execve(
			"/mnt/c/Windows/System32/PING.EXE",
			(char * const []){"/mnt/c/Windows/System32/PING.EXE",
			"google.com",
			NULL},
			NULL
			);
		// kill(getpid(), SIGKILL);
	}
	else
	{	
		waitpid(pid, &status, 0);
		printf("Success\n");
	}
	// execl(
	// 	"/mnt/c/Windows/System32/PING.EXE",
	// 	"/mnt/c/Windows/System32/PING.EXE",
	// 	"google.com",
	// 	NULL
	// 	);
	printf("End\n");
	return (0);
}

