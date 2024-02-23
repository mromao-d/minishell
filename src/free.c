#include "../includes/minishel.h"

// frees array of arrays
void	ft_free_arr(char **tokens)
{
	int	i;

	i = -1;
	while (tokens[++i])
		free(tokens[i]);
	free(tokens);
}
