#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	int	pid;
	int	x;
	int	y;

	if (pipe(fd) == -1)
	{
		perror("Pipe error\n");
		return (1);
	}
	pid = fork();
	// child process receives a number
	if (pid == 0)
	{
		close(fd[0]);
		printf("Input a number: ");
		scanf("%d", &x);
		if (write(fd[1], &x, sizeof(int)) == 1)
		{
			perror ("write error\n");
			return (2);
		}
		close(fd[1]);
	}
	// reads the output of the child process
	else
	{
		close(fd[1]);
		if (read (fd[0], &y, sizeof(int)) == -1)
		{
			perror ("read error\n");
			return (3);
		}
		close(fd[0]);
		printf("Got from child process %d\n", y);
	}
	// printf("Script Done!\n");
	return (0);
}
