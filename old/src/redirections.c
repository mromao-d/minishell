#include "../includes/minishel.h"// < should redirect input

// > should redirect output
// >> should redirect output in append mode
// < should redirect intput
// << should have a delimiter and read input untill the line with the delimiter is seen

int	ft_has_redirections(t_shell *shell)
{
	int	i;
	int	j;

	i = -1;
	while (shell->tokens && shell->tokens[++i])
	{
		j = -1;
		while (shell->tokens && shell->tokens[i][++j])
		{
			if (shell->tokens[i][j] == '\'')
				shell->s_quotes++;
			if (shell->tokens[i][j] == '"')
				shell->d_quotes++;
			if (((shell->tokens[i][j] == '>') || (shell->tokens[i][j] == '<')) && \
				(shell->s_quotes % 2 == 0) && (shell->d_quotes % 2 == 0))
				{
					shell->has_redirections = 1;
					return (1);
				}
		}
	}
	return (0);
}

// I will redirect the stdout.
void	ft_redirect_input(t_shell *shell)
{
	int	fd;
	int	pid;
	int	status;

	if (!ft_has_redirections(shell))
		return ;
	pid = fork();
	// (void) shell;
	(void) fd;
	if (pid < 0)
	{
		perror("fork error on redirect_input");
		exit(0) ;
	}
	if (pid == 0)
	{
		// fd = open(shell->tokens[0], O_WRONLY);
		fd = open("/mnt/c/Users/e352549/OneDrive - EDP/Documents/01. Documents/42/minishell/tes.txt", O_RDONLY | O_WRONLY | O_APPEND);
		if (fd < 0)
			return (perror("Error creating input redirect file"));
		// // dup2(fd, 0);
		execve("/usr/bin/cat", (char *[]){"/usr/bin/cat", "Makefile", NULL}, NULL);
		dup2(fd, STDIN_FILENO);
		// dup2(fd, STDOUT_FILENO);
		// // dup2(fd, STDERR_FILENO);
		// printf("STDIN_FILENO is %d and fd is:	%d\n", STDIN_FILENO, fd);
		// printf("STDIN_FILENO is %d\n", STDIN_FILENO);
		// // write(0, "Hello world\n", 12);
		// // ft_echo("askdnl apsdnkç açlsknd \n");
		// close (fd);
		kill(getpid(), SIGKILL);
	}
	else
		waitpid(pid, &status, 0);
	// printf("STDIN_FILENO is %d\n", STDIN_FILENO);
	return ;
}

