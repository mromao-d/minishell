#include "../includes/minishel.h"

// readline	-> displays prompt with message that I want

// // // rl_clear_history	-> clears history
// // // rl_on_new_line -> Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
// // // rl_replace_line	->	Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
// // // rl_redisplay	-> Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

// add_history	-> add history --> need this to add history of what was prompted

void	ft_free_arr(char **arr)
{
	int	i;
	
	i = -1;
	while (arr[++i])
		free(arr[i]);
	free(arr);
}

t_shell	*init_mini_shell(char **envp)
{
	t_shell	*minishell;

	minishell = calloc(sizeof(t_shell), 1);
	if (!minishell) {
		perror("Malloc ing minishell");
		exit (1);
	}
	minishell->envp = ft_get_paths(envp);
	return (minishell);
}

// stores each command in the t_cmds structure
t_cmds	*ft_init_cmds(t_shell *minishell)
{
	t_cmds	*head;
	t_cmds	*current;
	t_cmds	*tmp;
	char	**token;
	int		i;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	head = calloc(sizeof(t_cmds), 1);
	minishell->has_redirections = 0;
	if (!head) {
		perror ("malloc cmd on ft_init_cmds");
		exit (1);
	}
	i = 0;
	token = ft_split(minishell->prompt, ' ');
	if (strncmp(token[0], "./", 2) == 0) {
		strlcat(cwd, strchr(token[0], '/'), strlen(cwd) + strlen(token[0]) + 1);
		free(token[0]);
		free(minishell->tokens[0]);
		token[0] = strdup(cwd);
		minishell->tokens[0] = strdup(cwd);
		printf("cwd is: %s\n", cwd);
	}
	head->token = strdup(token[0]);
	head->next_cmd = NULL;
	current = head;
	i = 0;
	while (token[++i]) {
		tmp = calloc(sizeof(t_cmds), 1);
		if (!tmp) {
			perror ("malloc tmp on ft_init_cmds");
			exit (1);
		}
		tmp->token = strdup(token[i]);
		if ((strcmp(tmp->token, "<") == 0) || (strcmp(tmp->token, "<<") == 0) || \
			(strcmp(tmp->token, ">") == 0) || (strcmp(tmp->token, ">>") == 0))
			minishell->has_redirections = 1;
		tmp->next_cmd = NULL;
		current->next_cmd = tmp;
		current = tmp;
	}
	minishell->cmds = head;
	minishell->path = ft_get_builtin_name(minishell);
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

void	ft_print_arr(char **arr)
{
	while (*arr) {
		printf("%s\n", *arr);
		arr++;
	}
	return ;
}

// returns all paths from the environment
char	**ft_get_paths(char	**envp)
{
	char	**paths;

	while (*envp)
	{
		if (strncmp(*envp, "PATH", 4) == 0) {
			paths = ft_split(*envp + 5, ':');
			// printf("%s\n", *envp);
			break;
		}
		envp++;
	}
	// ft_print_arr(paths);
	return (paths);
}

// returns the executable name, if it has accesses.
// access returns zero if all is ok
// char	*ft_get_builtin_name(char **paths, char *cmd)
char	*ft_get_builtin_name(t_shell *shell)
{
	char	*s_path;
	char	*temp;
	char	**env;
	t_cmds	*head;
	// char	**fst_cmd;

	// fst_cmd = ft_split(cmd, ' ');
	if (strncmp(shell->prompt, "./", 2) == 0) {
		return (strdup(shell->cmds->token));
	}
	head = shell->cmds;
	while (head) {
		env = shell->envp;
		while (*env) {
			s_path = strdup(*env);
			temp = s_path;
			s_path = ft_strjoin(s_path, "/");
			free(temp);
			temp = s_path;
			s_path = ft_strjoin(s_path, head->token);
			if (!access(s_path, F_OK | R_OK)) {
				free(temp);
				return (s_path);
			}
			free(s_path);
			free(temp);
			env++;
		}
		head = head->next_cmd;
	}
	return NULL;
}

// saves the fd of all commands
void	ft_save_fd(t_shell *minishell)
{
	minishell->fd_in = dup(STDIN_FILENO);
	minishell->fd_out = dup(STDOUT_FILENO);
	return ;
}

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

void	ft_redirect_output(t_shell *shell)
{
	t_cmds	*head;

	head = shell->cmds;
	while (strcmp(head, ">") != 0)
	return ;
}

// executes the programme
void	ft_execve(t_shell *shell)
{
	int	fd[2];
	int	pid;
	int	status;

	if (shell->has_redirections == 1)
		return (ft_redirect_output(shell));
	if (pipe(fd) < 0) {
		perror ("pipe error on ft_execve\n");
		exit (1);
	}
	pid = fork();
	if (pid < 0) {
		perror ("fork error on ft_execve\n");
		exit (2);
	}
	if (pid == 0) {
        close(shell->fd_out);
        close(shell->fd_in);
        dup2(fd[0], shell->fd_in);
        dup2(fd[1], shell->fd_out);
        close(fd[0]);
        close(fd[1]);
		execve(shell->path, shell->tokens, NULL);
	}
	else {
        close(shell->fd_out);
        close(shell->fd_in);
        close(fd[0]);
        close(fd[1]);
		waitpid(pid, &status, 0);
	}
	// return (fd[0]);
	return ;
}

// // validates if has redirections
void	ft_redirect_fst_in(t_shell *shell)
{
	int	fd[2];
	int	pid;
	int	status;
	t_cmds	*head;

	if (strcmp(shell->cmds->token, "<") != 0)
		return ;
	head = shell->cmds;
	head = head->next_cmd;
	int	fdd = open(shell->cmds->next_cmd->token, O_RDONLY);
	if (fdd < 0) {
		perror ("fd opening error");
		exit (1);
	}
	if (pipe(fd) < 0) {
		perror ("pipe error on has_redirections\n");
		exit (2);
	}
	pid = fork();
	if (pid == 0) {
		dup2(fdd, STDIN_FILENO);
		dup2(fd[1], shell->fd_out);
		close(fdd);
		close(fd[0]);
		close(fd[1]);
		execve(shell->path, (char *[]){shell->path, NULL}, NULL);
	}
	else {
		close(fd[0]);
		close(fd[1]);
		close(fdd);
		waitpid(pid, &status, 0);
	}
}

// executes commands
int	ft_exec_cmd(t_shell *shell)
{
	ft_save_fd(shell);
	if (strcmp(shell->prompt, "exit") == 0) {
		ft_free_cmd(&shell->cmds);
		ft_free_arr(shell->tokens);
		free(shell->path);
		free(shell->prompt);
		ft_free_arr(shell->envp);
		free(shell);
		exit(0);
	}
	if (strcmp(shell->tokens[0], "clear") == 0)
		return (printf("\033[2J\033[H"));
	if (strcmp(shell->tokens[0], "<") != 0)
		ft_execve(shell);
	ft_redirect_fst_in(shell);		//this is only for the commands that start with "<"
	return (0);
}

// int main(int argc, char **argv, char **envp) 
// {
// 	t_shell	*mini_shell;

// 	if (argc > 1)
// 		return (0);
// 	(void) argv;
// 	(void) argc;
// 	(void) envp;
// 	mini_shell = init_mini_shell(envp);
// 	while (1)
// 	{
// 		mini_shell->prompt = readline("minishell$: ");
// 		if (!mini_shell->prompt)
// 		{
// 			perror("prompt error");
// 			return (1);
// 		}
// 		mini_shell->tokens = ft_split(mini_shell->prompt, ' ');
// 		mini_shell->cmds = ft_init_cmds(mini_shell);
// 		add_history(mini_shell->prompt);
// 		// printf("path is: %s\n", mini_shell->path);
// 		ft_exec_cmd(mini_shell);
// 		ft_free_cmd(&mini_shell->cmds);
// 		ft_free_arr(mini_shell->tokens);
// 		free(mini_shell->path);
// 		free(mini_shell->prompt);
// 	}
// 	ft_free_arr(mini_shell->envp);
// 	free(mini_shell);
// 	return (0);
// }





// dup2(oldfd, newfd);
// the oldfd is copied into the newfd
