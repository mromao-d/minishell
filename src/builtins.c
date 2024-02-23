#include "../includes/minishel.h"

// builtins are
	// echo with option -n
	// cd with only a relative or a absolute path
	// pwd with no options
	// export with no options
	// unset with no options
	// env with no options or arguments
	// exit with no options

// receives the path and relocates to that direction
// returns 0 if everything is ok
int	ft_cd(char *path)
{
	;
}

// prints current directory using getcwd. It returns zero if it works.
// if it returns null is because there is no working directory
int	ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (pwd == NULL)
	{
		perror("failed to get current directory!\n");
		return (-1);
	}
	printf("current directory is: %s\n", pwd);
	free(pwd);
	return (0);
}

