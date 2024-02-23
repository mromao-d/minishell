#include "../includes/minishel.h"

// readline	-> displays prompt with message that I want

// // // rl_clear_history	-> clears history
// // // rl_on_new_line -> Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
// // // rl_replace_line	->	Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
// // // rl_redisplay	-> Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

// add_history	-> add history --> need this to add history of what was prompted


// execv executes the programe with the needed arguments
// Need to fork the process-- otherwise it will end my process and close my prompt
// 		The child process pid equals zero.
// should return -1 (or zero ???)
int	ft_execv(const char *path, char *const *argv)
{
	int	pid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		return (-1);
	}
	if (pid == 0)
	{	
		execv(path, argv);
		perror("execv");
		kill(getpid(), SIGKILL);
	}
	else
		waitpid(pid, &status, 0);
	return (-1);
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
			ft_exit();
		if (ft_strcmp(prompt, "pwd") == 0)
			ft_pwd();
		if (ft_strncmp(prompt, "echo", 4) == 0)
			ft_get_env(prompt);
		if (ft_strncmp(prompt, "./", 2) == 0)
			ft_execv(prompt, NULL);
		if (strcmp(prompt, "clear") == 0)
			printf("\033[2J\033[H");
		add_history(prompt);
		free((void *) prompt);
	}
	rl_clear_history();
	// ft_clean(prompt);
	return 0;
}
