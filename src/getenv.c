#include "../includes/minishel.h"

// store the arguments
char	**ft_save_args(const char *args)
{
	char	**output;

	output = ft_split(args, ' ');
	return (output);
}

void	ft_print_splited(char **splited)
{
	int	i;

	i = -1;
	while (splited[++i])
		printf("%s\n", splited[i]);
	return ;
}

// returns the environment variable
// to return the "PATH" environment, just have to getenv("PATH")
// types of env variables: USER, TERM, HOME & PATH
char	*ft_get_env(const char *env)
{
	while (*env != ' ')
		env++;
	env++;
	// ft_print_splited(ft_save_args(env));
	if (!(ft_strcmp(env, "PATH") == 0 || ft_strcmp(env, "HOME") == 0 || ft_strcmp(env, "TERM") == 0 || ft_strcmp(env, "USER") == 0))	
	{	
		perror("No valid env\n");
		return (NULL);
	}
	printf("%s\n", getenv(env));
	return (getenv(env));
}
