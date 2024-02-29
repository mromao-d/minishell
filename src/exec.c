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
		execve(path, arg, envp);
		perror("execve on ft_execve");
		kill(getpid(), SIGKILL);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}

int	ft_deal_execs(char *prompt)
{
	char	*env;
	char    **paths;
	char	**tokens;
	int     i;
	char	*joined;

	env = getenv("PATH");
	paths = ft_split(env, ':');
	tokens = ft_split(prompt, ' ');
	(void) prompt;
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
		// printf("joined is: %s\n", joined);
		if (access(joined, X_OK) == 0 && ft_strncmp(joined, "/usr", 4) != 0){
			// printf("joined is %s\n", joined);
			ft_execve(joined, (char *[]){joined, tokens[1], NULL}, NULL);}
		// 	execve("/usr/bin/cat", (char *[]){joined, tokens[1], NULL}, NULL);
		// 	// execve("/usr/bin/cat/", (char *const *) "./Makefile", NULL);
		free(joined);
	}
	ft_free_arr(paths);
	ft_free_arr(tokens);
	return (0);
}