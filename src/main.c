#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

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
// should return -1 (or zero ???)
int	ft_execv(const char *path, char *const *argv)
{
	if (!(ft_strncmp(path, "./", 2) == 0))
		return (12);
	(void) argv;
	execv(path, NULL);
	return (-1);
}

// returns the environment variable
// to return the "PATH" environment, just have to getenv("PATH")
// types of env variables: USER, TERM, HOME & PATH
char	*ft_get_env(const char *env)
{
	if (!(ft_strcmp(env, "PATH") == 0 || ft_strcmp(env, "HOME") == 0 || ft_strcmp(env, "TERM") == 0 || ft_strcmp(env, "USER") == 0))	
		return ("No valid env");
	printf("%s\n", getenv(env));
	return (getenv(env));
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
		ft_get_env(prompt);
		ft_execv(prompt, NULL);
		add_history(prompt);
		free((void *) prompt);
	}
	return 0;
}
