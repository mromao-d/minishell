#include "../includes/minishel.h"

// builtins are
	// echo with option -n
	// cd with only a relative or a absolute path
	// pwd with no options
	// export with no options
	// unset with no options
	// env with no options or arguments
	// exit with no options

// receives the path and relocates to that direction using chdir
// returns 0 if everything is ok
int	ft_cd(char *path)
{
	char	**tokens;
	char	*arg;
	char	*substr;
	int		nb_wrds;

	substr = 0;
	if (path == 0)
		return (0);
	tokens = ft_split(path, ' ');
	nb_wrds = ft_count_words_arr(tokens);
	if (nb_wrds > 2)
	{
		ft_free_arr(tokens);
		printf("-minishel: -cd: Too many tokens\n");
		return (1);
	}
	if (tokens[1][0] == '~')
	{
		substr = ft_substr(tokens[1], 1, ft_strlen(tokens[1]) - 1);
		arg = ft_strjoin(getenv("HOME"), substr);
	}
	else
		arg = ft_strdup(tokens[1]);
	if (nb_wrds == 1)
		chdir(getenv("HOME"));
	else
		if (chdir(arg))
			perror("-minishel: -cd: %s: No such file or directory\n");
	ft_free_arr(tokens);
	free(arg);
	free(substr);
	return (0);
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
