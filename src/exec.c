#include "../includes/minishel.h"

// The PATH environment variable is an important security control. 
// It specifies the directories to be searched to find a command.

int	ft_execve(const char *path, char *const arg[], char *const envp[])
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork error on ft_execve");
		return (-1);
	}
	if (pid == 0)
	{
		if (execve(path, arg, envp) == -1)
		{
			perror("execve on ft_execve");
			return (-1);
		}
		kill(getpid(), SIGKILL);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}

// runs all executables
int	ft_run_program(char **tokens, char **paths)
{
	char	cd[CWD_SIZE];
	char	*path;

	getcwd(cd, sizeof(cd));
	path = malloc(sizeof(char) * ft_strlen(cd) + 1);
	if (!path)
		perror("shit happened malloc ing path on ft_run_program\n");
	ft_bzero(path, ft_strlen(cd) + 1);
	ft_strcpy(path, cd);
	if (cd == NULL)
	{	
		perror("ft_run_program getcwd error\n!");
		return (-1);
	}
	ft_strlcat(cd, ft_strchr(tokens[0], '/'), ft_strlen(cd) + ft_strlen(tokens[0]) + 1);
	ft_execve(cd, (char *[]){cd, NULL}, NULL);
	ft_free_arr(tokens);
	ft_free_arr(paths);
	free(path);
	return (0);
}

int	ft_deal_execs_aux(char **paths, char **tokens)
{
	int		i;
	char	*joined;

	i = -1;
	while (paths[++i])
	{
		joined = NULL;
		joined = malloc(sizeof(char) * (ft_strlen(paths[i]) + ft_strlen(tokens[0]) + 3));
		if (!joined)
		{
			perror("ft_deal_execs malloc error!");
			return (1);
		}
		ft_bzero(joined, ft_strlen(paths[i]) + ft_strlen(tokens[0]) + 3);
		ft_strlcpy(joined, paths[i], ft_strlen(paths[i]) + 1);
		joined[ft_strlen(joined)] = '/';
		ft_strlcat(joined, tokens[0], ft_strlen(joined) + ft_strlen(tokens[0]) + 1);
		joined[ft_strlen(joined) + 1] = 0;
		if (access(joined, X_OK) == 0 && ft_strncmp(joined, "/usr", 4) != 0)
			ft_execve(joined, (char *[]){joined, tokens[1], NULL}, NULL);
		free(joined);
	}
	ft_free_arr(paths);
	ft_free_arr(tokens);
	return (0);
}

//		/bin runs all executable files that are part of the core operating system.
//		/usr/bin contains executable files that are not part of the core operating system.
int	ft_deal_execs(char *prompt)
{
	char	*env;
	char	**paths;
	char	**tokens;

	env = getenv("PATH");
	paths = ft_split(env, ':');
	tokens = ft_split(prompt, ' ');
	if (ft_strncmp(tokens[0], "./", 2) == 0)
		return (ft_run_program(tokens, paths));
	// (void) prompt;
	if (ft_count_words_arr(tokens) == 1)
	{	
		if (access(tokens[0], X_OK) == 0 && ft_strncmp(tokens[0], "/usr", 4) != 0)
			ft_execve(tokens[0], (char *[]){tokens[0], NULL}, NULL);
	}
	else
		return(ft_deal_execs_aux(paths, tokens));
	ft_free_arr(paths);
	ft_free_arr(tokens);
	return (0);
}
