#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>

// readline	-> displays prompt with message that I want

// // // rl_clear_history	-> clears history
// // // rl_on_new_line -> Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
// // // rl_replace_line	->	Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
// // // rl_redisplay	-> Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

// add_history	-> add history --> need this to add history of what was prompted


int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

int	ft_strncmp(const char *s1, const char *s2, size_t	i)
{
	size_t	j;

	if (i == 0)
		return (0);
	j = 0;
	while (*s1 && *s1 == *s2 && j < i - 1)
	{
		s1++;
		s2++;
		j++;
	}
	return ((int)*s1 - (int)*s2);
}

// execv executes the programe with the needed arguments
// Need to fork the process-- otherwise it will end my process and close my prompt
// 		The child process pid equals zero.
// should return -1 (or zero ???)
int	ft_execv(const char *path, char *const *argv)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid == 0)
	{	
		execv(path, argv);
		kill(getpid(), SIGKILL);
	}
	else
		waitpid(pid, &status, 0);
	return (-1);
}

// returns the environment variable
// to return the "PATH" environment, just have to getenv("PATH")
// types of env variables: USER, TERM, HOME & PATH
char	*ft_get_env(const char *env)
{
	if (!(ft_strcmp(env, "PATH") == 0 || ft_strcmp(env, "HOME") == 0 || ft_strcmp(env, "TERM") == 0 || ft_strcmp(env, "USER") == 0))	
	{	
		printf("No valid env\n");
		return (NULL);
	}
	printf("%s\n", getenv(env));
	return (getenv(env));
}


void	ft_clean_args(char **kargs, int argc)
{
	int	i;

	i = -1;
	while ( ++i < argc)
		if (kargs[i])
			free(kargs[i]);
	return ;
}

// cleans argument, if it exists
void	ft_clean(char *kargs)
{
	if (kargs)
		free(kargs);
	return ;
}

// exits programm
void	ft_exit(void)
{
	exit(0);
}


int main(void) 
{
	char	*prompt;

    while (1)
	{
		prompt = readline("minishell$: ");
		if (!prompt)
		{
			printf("\n");
			break;
		}
		if (ft_strcmp(prompt, "exit") == 0)
		{
			// free((void *) prompt);
			// rl_clear_history();
			ft_exit();
		}
		ft_get_env(prompt);
		add_history(prompt);
		// if (env)
		// 	free((void *) env);
		if (ft_strncmp(prompt, "./", 2) == 0)
			ft_execv(prompt, NULL);
		free((void *) prompt);
	}
	rl_clear_history();
	// ft_clean(prompt);
	return 0;
}
