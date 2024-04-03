#include "../includes/minishel.h"

// readline	-> displays prompt with message that I want

// // // rl_clear_history	-> clears history
// // // rl_on_new_line -> Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
// // // rl_replace_line	->	Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
// // // rl_redisplay	-> Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

// add_history	-> add history --> need this to add history of what was prompted

// frees array
void	ft_free_arr(char **arr)
{
	int	i;
	
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
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

// frees the environment structure
void	ft_free_env(t_env *env)
{
	t_env	*head;
	t_env	*next;

	head = env;
	next = head;
	while (next) {
		head = next;
		next = next->next_node;
		free(head->var_name);
		// free(head->var_value);
		free(head);
	}
}

// prints array
void	ft_print_arr(char **arr)
{
	char	**head;

	head = arr;
	while (*head) {
		printf("%s\n\n", *head);
		head++;
	}
	return ;
}

// prints array
void	ft_print_env(t_env *env)
{
	t_env	*head;

	head = env;
	while (head) {
		printf("%s\n\n", head->var_name);
		head=head->next_node;
	}
	return ;
}

// prints cmds
void	ft_print_cmds(t_cmds *cmds)
{
	t_cmds	*head;

	head = cmds;
	while (head) {
		printf("%s\n\n", head->token);
		head=head->next_cmd;
	}
	return ;
}

// counts the elements on an array
int	ft_count_arr(char **arr)
{
	int	i;

	i = 0;
	while (*arr) {
		i++;
		arr++;
	}
	return (i);
}

// converts each list of commands into a array

// saves the fd of all commands
void	ft_save_fd(t_shell *minishell)
{
	minishell->fd_in = dup(STDIN_FILENO);
	minishell->fd_out = dup(STDOUT_FILENO);
	return ;
}

t_shell	*ft_init_shell(char **envp)
{
	t_shell	*shell;

	shell = calloc(sizeof(t_shell), 1);
	if (!shell) {
		perror ("init shell error!\n");
		exit (1);
	}
	shell->env = ft_init_env(envp);
	// ft_save_fd(shell);
	return (shell);
}

// saves the env variables
t_env	*ft_init_env(char **envp)
{
	t_env	*env;
	t_env	*current;
	t_env	*next;
	int		i;

	env = calloc(sizeof(t_env), 1);
	if (!env) {
		perror ("env creation\n");
		exit (1);
	}
	i = 0;
	env->var_name = ft_inv_strchr(*envp, '=');
	env->var_value = strchr(*envp, '=');
	env->next_node = NULL;
	env->order = i;
	current = env;
	while (*envp && ++i) {
		next = calloc(sizeof(t_env), 1);
		next->order = i;
		next->var_name = ft_inv_strchr(*envp, '=');
		next->var_value = strchr(*envp, '=');
		next->next_node = NULL;
		current->next_node = next;
		current = current->next_node;
		envp++;
	}
	return (env);
}

void	ft_init_cmds(t_shell *shell)
{
	t_cmds	*head;
	t_cmds	*current;
	t_cmds	*next;
	char	**splited;
	int		i;

	splited = ft_split(shell->prompt, ' ');
	head = calloc(sizeof(t_cmds), 1);
	if (!head) {
		perror ("calloc cmds in ft_init_cmds");
		exit (3);
	}
	i = 0;
	shell->cmds = head;
	shell->cmds->token = strdup(splited[i]);
	shell->cmds->next_cmd = NULL;
	current = shell->cmds;
	while (splited[++i]) {
		next = calloc(sizeof(t_cmds), 1);
		if (!next) {
			perror ("calloc next in ft_init_cmds");
			exit (3);
		}
		next->token = strdup(splited[i]);
		next->next_cmd = NULL;
		current->next_cmd = next;
		current = current->next_cmd;
	}
	ft_free_arr(splited);
	return ;
}

// prints current directory
void	ft_print_cd()
{
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return ;
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	*shell;
	// t_cmds	*head;

	(void) argc;
	(void) argv;
	shell = ft_init_shell(envp);
	while (1) {
		shell->prompt = readline("minishel$ ");
		ft_save_fd(shell);
		add_history(shell->prompt);
		ft_init_cmds(shell);
		// ft_print_cmds(shell->cmds);
		// head = shell->cmds;
		// while (shell->cmds) {
		// 	// ft_execve(shell, head->token);
		// 	ft_execve_(shell);
		// 	shell->cmds = shell->cmds->next_cmd;
		// 	// head = shell->cmds;
		// }
		// head = shell->cmds;
		// ft_simple_redirect(shell);
		// ft_simple_redirect_new(shell);
		ft_find_path(shell);
		ft_execve_(shell);
		free(shell->prompt);
		// printf("path is: %s\n", shell->path);
		// dup2(shell->fd_in, STDIN_FILENO);
		// dup2(shell->fd_out, STDOUT_FILENO);
		// close(shell->fd_in);
		// close(shell->fd_out);
		// if (shell->path && shell->path != NULL)
		// 	free(shell->path);
		ft_free_cmd(&shell->cmds);
	}
	ft_free_env(shell->env);
	free(shell);
	return (0);
}



// dup2(oldfd, newfd);
// the oldfd is copied into the newfd
