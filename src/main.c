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

// validate if all quotes are closed (even numbers)
// returns zero if yes
int	ft_validate_quotes(char *arg)
{
	int	single_q;
	int	double_q;
	int	i;

	single_q = 0;
	double_q = 0;
	i = -1;
	while (arg[++i])
	{
		if (arg[i] == '\'')
			single_q++;
		if (arg[i] == '"')
			double_q++;
	}
	if (single_q % 2 == 0 && double_q % 2 == 0)
		return (0);
	printf("unclosed quotes!\n");
	return (1);
}

int main(int argc, char **argv, char **envp) 
{
	char	*prompt;

	if (argc > 1)
		return (0);
	(void) argv;
    while (1)
	{
		prompt = readline("minishell$: ");
		ft_get_env("PATH");
		if (!prompt)
		{
			printf("\n");
			break;
		}
		if (ft_strcmp(prompt, "exit") == 0)
			ft_exit();
		ft_deal_built_ins(prompt);
		ft_deal_execs(prompt);
		if (ft_strcmp(prompt, "env") == 0)
			ft_env(envp);
		// if (ft_strncmp(prompt, "./", 2) == 0)
		// 	ft_execv(prompt, NULL);
		if (strcmp(prompt, "clear") == 0)
			printf("\033[2J\033[H");
		add_history(prompt);
		free((void *) prompt);
		prompt = 0;
	}
	rl_clear_history();
	// ft_clean(prompt);
	return 0;
}
