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

// split commands by space
// t_cmds	*ft_split_space(char *prompt)
// {
// 	;
// }

// split commands by s_quotes
// t_cmds	*ft_split_space(char *prompt)
// {
// 	;
// }

// stores each command in the t_cmds structure
t_cmds	*ft_init_cmds(char *prompt)
{
	t_cmds	*head;
	t_cmds	*current;
	t_cmds	*tmp;
	char	**token;
	int		i;

	head = malloc(sizeof(t_cmds));
	if (!head) {
		perror ("malloc cmd on ft_init_cmds");
		exit (1);
	}
	i = 0;
	token = ft_split(prompt, ' ');
	head->token = strdup(token[0]);
	head->next_cmd = NULL;
	current = head;
	i = 0;
	while (token[++i]) {
		tmp = malloc(sizeof(t_cmds));
		if (!tmp) {
			perror ("malloc tmp on ft_init_cmds");
			exit (1);
		}
		tmp->token = strdup(token[i]);
		tmp->next_cmd = NULL;
		current->next_cmd = tmp;
		current = tmp;
		printf("cmd is: %s\n", token[i]);
	}
	ft_free_arr(token);
	return (head);
}

// frees t_cmds structure
void	ft_free_cmd(t_cmds **cmds)
{
	t_cmds	*node;
	t_cmds	*nxt_node;

	node = *cmds;
	while (node) {
		nxt_node = node->next_cmd;
		free(node->token);
		free(node);
		node = nxt_node;
	}
	return ;
}

// int	ft_execve(char **envp, )

// int	ft_execve_redir(t_cmds *cmds)
// {
// 	;
// }

// int	ft_struct_redirections(t_cmds *cmds)
// {
// 	t_cmds	*tmp;

// 	tmp = cmds;
// 	while (tmp) {
// 		if (strcmp(tmp->token, "<") == 0)
// 			return(ft_redirect_input_new());
// 		tmp = tmp->next_cmd;
// 	}
// }

// returns all paths from the environment
char	**ft_get_paths(char	**envp)
{
	char	**paths;

	while (*envp)
	{
		if (strncmp(*envp, "PATH", 4) == 0)
			// printf("%s\n", *envp);
			paths = ft_split(*envp + 5, ':');
		envp++;
	}
	ft_print_arr(paths);
	return (paths);
}

// returns the executable name, if it has accesses.
// access returns zero if all is ok
char	*ft_get_exec_name(char **paths, char *cmd)
{
	char	*s_path;
	char	*temp;
	char	**fst_cmd;

	fst_cmd = ft_split(cmd, ' ');
	while (*paths) {
		s_path = strdup(*paths);
		temp = s_path;
		s_path = ft_strjoin(s_path, fst_cmd[0]);
		if (!access(s_path, F_OK | R_OK)) {
			free(temp);
			ft_free_arr(fst_cmd);
			return (s_path);
		}
		free(s_path);
		free(temp);
		paths++;
	}
	ft_free_arr(fst_cmd);
	return NULL;
}

void	ft_exec_cmd()
{
	;
}

int main(int argc, char **argv, char **envp) 
{
	char	*prompt;
	t_cmds	*cmd;
	char	**paths;

	if (argc > 1)
		return (0);
	(void) argv;
	(void) argc;
	(void) envp;
	paths = ft_get_paths(envp);
	while (1)
	{
		prompt = readline("minishell$: ");
		if (!prompt)
		{
			perror("prompt error");
			return (1);
		}
		cmd = ft_init_cmds(prompt);
		ft_exec_cmd();
		ft_free_cmd(&cmd);
		(void) cmd;
	}
	ft_free_arr(paths);
	return (0);
}

// int main(int argc, char **argv, char **envp) 
// {
// 	char	*prompt;
// 	t_shell	*shell;

// 	if (argc > 1)
// 		return (0);
// 	(void) argv;
// 	(void) envp;
//     while (1)
// 	{
// 		prompt = readline("minishell$: ");
// 		if (!prompt)
// 		{
// 			printf("\n");
// 			break;
// 		}
// 		// shell->in = dup(STDIN_FILENO);
// 		// shell->out = dup(1);
// 		// shell->err = dup(2);
// 		shell = ft_shell(prompt);
// 		ft_deal_built_ins(shell);
// 		ft_deal_execs(shell);
// 		ft_redirect_input(shell);
// 		// ft_redirect_input();
// 		if (strcmp(shell->tokens[0], "clear") == 0)
// 			printf("\033[2J\033[H");
// 		add_history(prompt);
// 		ft_free_shell(shell);
// 		free((void *) prompt);
// 	}
// 	rl_clear_history();
// 	return 0;
// }
