#include "../includes/minishel.h"// < should redirect input

// > should redirect output
// < should have a delimiter and read input untill the line with the delimiter is seen
// < should redirect output in append mode

void	ft_redirect_input(char *str)
{
	int	fd;

	fd = open(str, O_RDONLY);
	if (fd < 0)
		return (perror("Error creating input redirect file"));
	dup2(fd, STDIN_FILENO);
	close (fd);
	return ;
}

