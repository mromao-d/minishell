#include "../includes/minishel.h"

// readline	-> displays prompt with message that I want

// // // rl_clear_history	-> clears history
// // // rl_on_new_line -> Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
// // // rl_replace_line	->	Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
// // // rl_redisplay	-> Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

// add_history	-> add history --> need this to add history of what was prompted

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
	t_shell	*shell;

	if (argc > 1)
		return (0);
	(void) argv;
	(void) envp;
    while (1)
	{
		prompt = readline("minishell$: ");
		if (!prompt)
		{
			printf("\n");
			break;
		}
		shell = ft_shell(prompt);
		ft_deal_built_ins(shell);
		ft_deal_execs(prompt);
		if (strcmp(shell->tokens[0], "clear") == 0)
			printf("\033[2J\033[H");
		add_history(prompt);
		ft_free_shell(shell);
		free((void *) prompt);
	}
	rl_clear_history();
	return 0;
}
