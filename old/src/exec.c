#include "../includes/minishel.h"

// The PATH environment variable is an important security control. 
// It specifies the directories to be searched to find a command.

// execv executes the programe with the needed arguments
// Need to fork the process-- otherwise it will end my process and close my prompt
// 		The child process pid equals zero.
// should return -1 (or zero ???)
// forks the process and runs all shits on child process (pid == 0)
// it is what I need to use when I want to use the execve function
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

// runs all executables that start with './'
int	ft_run_program(char **tokens, char **paths)
{
	char	cd[CWD_SIZE];
	char	*path;

	getcwd(cd, sizeof(cd));
	path = malloc(sizeof(char) * ft_strlen(cd) + 1);
	if (!path)
		perror("shit happened malloc ing path on ft_run_program\n");
	ft_bzero(path, ft_strlen(cd) + 1);
	ft_strcpy_v2(path, cd);
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

// 
int	ft_deal_execs_aux(char **paths, char **tokens)
{
	int		i;
	char	*joined;
	int		exit;

	i = -1;
	exit = 0;
	joined = 0;
	if (access(tokens[0], X_OK) == 0)
		return (ft_execve(tokens[0], tokens, NULL));
	while (paths[++i] && (exit == 0))
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
		if (access(joined, X_OK) == 0 && ft_execve(joined, tokens, NULL) == 0)
			exit = 1;
		free(joined);
	}
	// if (exit != 1)
	// 	printf("Error | wrong cmd\n");
	return (0);
}

//		/bin runs all executable files that are part of the core operating system.
//		/usr/bin contains executable files that are not part of the core operating system.
int	ft_deal_execs(t_shell *shell)
{
	char	*env;
	char	**paths;

	env = 0;
	paths = 0;
	if (ft_has_redirections(shell))
		return (0);
	env = getenv("PATH");
	paths = ft_split(env, ':');
	ft_deal_execs_aux(paths, shell->tokens);
	ft_free_arr(paths);
	return (0);
}
