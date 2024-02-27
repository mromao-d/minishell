#include "../includes/minishel.h"

// The PATH environment variable is an important security control. 
// It specifies the directories to be searched to find a command.

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
		// printf("%s\n", ft_strjoin(ft_strjoin(env, "/"), promt));
		// if (!access(ft_strjoin(ft_strjoin(env, "/"), promt), X_OK))
			// printf("no access here: %s\n", env);
		// else
			// ft_execv(ft_strjoin(ft_strjoin(env, "/"), promt), NULL);
			// printf("%s\n", ft_strjoin(ft_strjoin(env, "/"), promt));
		// env++;
		// printf("%s\n", *paths);
		// printf("%s\n\n\n", env);
		joined = malloc(sizeof(char) * (ft_strlen(paths[i]) * ft_strlen(tokens[0]) + 2));
		while (*joined)
		{
			*joined = 0;
			joined++;
		}
		ft_strlcat(joined, paths[i], ft_strlen(paths[i]));
		joined[ft_strlen(joined)] = '/';
		ft_strlcat(joined, tokens[0], ft_strlen(joined) + ft_strlen(tokens[0]));
		// joined = ft_strjoin(ft_strcat(paths[i], "/"), prompt);
		// joined = ft_strjoin(paths[i], "/cat");
		printf("%s access is: %d\n", joined, access(joined, X_OK));
		// printf("%s\n", paths[i]);
		// (*paths)++;
		free(joined);
		joined = 0;
	}
	ft_free_arr(paths);
	// free(env);
	return (0);
}