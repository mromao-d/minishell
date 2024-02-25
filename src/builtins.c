#include "../includes/minishel.h"

// builtins are
	// echo with option -n
	// cd with only a relative or a absolute path
	// pwd with no options
	// export with no options
	// unset with no options
	// env with no options or arguments
	// exit with no options

void	ft_deal_built_ins(char *prompt)
{
	if (ft_strcmp(prompt, "pwd") == 0)
		ft_pwd();
	if (ft_strncmp(prompt, "cd", 2) == 0)
		ft_cd(prompt);
	if (ft_strncmp(prompt, "echo", 4) == 0)
		ft_echo(prompt);
	return ;
}

// void	ft_deal_quotes(char *str)
// {
// 	;
// }

// redo the echo command. Still have to add:
	//  "$" possibilities
	// "" and '' possibilities
int	ft_echo(char *prompt)
{
	char	**tokens;
	int		i;
	int		wrds;

	tokens = ft_split(prompt, ' ');
	wrds = ft_count_words_arr(tokens);
	if (!(prompt[4] == ' ' || prompt[4] == 0))
	{
		printf("%s: command not found\n", tokens[0]);
		ft_free_arr(tokens);
		return (0);
	}
	if (ft_strcmp(prompt, "echo") == 0)
		return(printf("\n"));
	i = 0;
	if (ft_strcmp(tokens[1], "-n") != 0)
	{
		while (tokens[++i] && (i + 1) < wrds)
			printf("%s ", tokens[i]);
		printf("%s", tokens[i]);
		ft_free_arr(tokens);
		return (printf("\n"));
	}
	else
	{
		while (tokens[++i + 1] && (i + 2) < wrds)
			printf("%s ", tokens[i + 1]);
		printf("%s", tokens[i + 1]);
		ft_free_arr(tokens);
		return (0);
	}
}

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
	printf("%s\n", pwd);
	free(pwd);
	return (0);
}
