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
	while (shell->tokens[++i])
	{
		j = -1;
		while (shell->tokens[i][++j])
			if ((shell->tokens[i][j] == '>') || (shell->tokens[i][j] == '<'))
				return (1);
	}
	return (0);
}

void	ft_redirect_input(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (perror("Error creating input redirect file"));
	dup2(fd, STDIN_FILENO);
	printf("fd is:	%d\n", fd);
	close (fd);
	return ;
}

