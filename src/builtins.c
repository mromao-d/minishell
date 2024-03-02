#include "../includes/minishel.h"

// builtins are
	// echo with option -n
	// cd with only a relative or a absolute path
	// pwd with no options
	// export with no options
	// unset with no options
	// env with no options or arguments
	// exit with no options

// exits programm
void	ft_exit(void)
{
	exit(0);
}

void	ft_deal_built_ins(t_shell *shell)
{
	// if (ft_strcmp(shell->tokens[0], "pwd") == 0)
	// 	ft_pwd();
	if (ft_strncmp(shell->tokens[0], "cd", 2) == 0)
		ft_cd(shell->tokens[0]);
	if (ft_strncmp(shell->tokens[0], "echo", 4) == 0)
		ft_echo(shell->promt);
	if (ft_strcmp(shell->tokens[0], "exit") == 0)
		ft_exit();
	if (ft_strcmp(shell->tokens[0], "env") == 0)
		ft_env(shell->envp);
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

	if (ft_validate_quotes(prompt) != 0)
		return (-1);
	tokens = ft_split(prompt, ' ');
	wrds = ft_count_words_arr(tokens);
	i = 0;
	if (ft_strcmp(tokens[1], "-n") == 0)
	{
		while (tokens[++i + 1] && (i + 2) < wrds)
			printf("%s ", tokens[i + 1]);
		printf("%s", tokens[i + 1]);
		ft_free_arr(tokens);
	}
	return (0);
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

int	ft_env(char **envp)
{
	int		i;
	char	**lines;

	i = -1;
	while (envp[++i])
	{
		lines = ft_split(envp[i], '=');
		printf("%i %s = %s\n", i, lines[0], lines[1]);
		ft_free_arr(lines);
		lines = 0;
	}
	return (0);
}
