#include "../includes/minishel.h"

t_shell	*ft_shell(char *prompt)
{
	t_shell *shell;

	shell = calloc(sizeof(t_shell), 1);
	if (!shell)
		perror("Error calloc ing shell on ft_shell\n");
	shell->prompt = strdup(prompt);
	shell->tokens = ft_split(prompt, ' ');
	// shell->s_quotes = 0;
	// shell->d_quotes = 0;
	// shell->in = dup(STDIN_FILENO);
	// shell->out = dup(STDOUT_FILENO);
	// shell->err = dup(STDERR_FILENO);
	return (shell);
}

// void	ft_print_arr(t_shell *shell)
// {
// 	char **str;

// 	str = shell->tokens;
// 	while (*str)
// 	{
// 		printf("%s\n", *str);
// 		str++;
// 	}
// 	return ;
// }

void	ft_free_shell(t_shell *shell)
{
	char	**str;

	str = shell->tokens;
	while (*str)
	{
		// printf("token is: %s\n", *str);
		free(*str);
		str++;
	}
	free(shell->tokens);
	free(shell->prompt);
	free(shell);
	// return (0);
	return ;
}

// int	ft_has_redirections(t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	while (shell->tokens)
// 	{}
// }
