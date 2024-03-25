#include "../includes/minishel.h"

// readline	-> displays prompt with message that I want

// // // rl_clear_history	-> clears history
// // // rl_on_new_line -> Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline.
// // // rl_replace_line	->	Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. If clear_undo is non-zero, the undo list associated with the current line is cleared.
// // // rl_redisplay	-> Change what’s displayed on the screen to reflect the current contents of rl_line_buffer.

// add_history	-> add history --> need this to add history of what was prompted

void	ft_free_arr(char **arr)
{
	while (*arr) {
		free(*arr);
		arr++;
	}
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
	minishell->path = calloc(sizeof(char), 1);
	if (!minishell->path) {
		perror ("minishell path calloc shit");
		exit (2);
	
	}
	// minishell->envp = calloc(sizeof(char *), 1);
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

	head = calloc(sizeof(t_cmds), 1);
	if (!head) {
		perror ("malloc cmd on ft_init_cmds");
		exit (1);
	}
	i = 0;
	token = ft_split(minishell->prompt, ' ');
	head->token = token[0];
	head->next_cmd = NULL;
	current = head;
	i = 0;
	while (token[++i]) {
		tmp = calloc(sizeof(t_cmds), 1);
		if (!tmp) {
			perror ("malloc tmp on ft_init_cmds");
			exit (1);
		}
		// tmp->token = strdup(token[i]);
		tmp->token = token[i];
		tmp->next_cmd = NULL;
		current->next_cmd = tmp;
		current = tmp;
	}
	minishell->cmds = head;
	// minishell->path = ft_get_builtin_name(minishell->envp, minishell->cmds->token);
	minishell->path = ft_get_builtin_name(minishell);
	// ft_free_arr(token);
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
			printf("%s\n", *envp);
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
	head = shell->cmds;
	while (head) {
		env = shell->envp;
		while (*env) {
			s_path = strdup(*env);
			temp = s_path;
			// s_path = ft_strjoin(s_path, fst_cmd[0]);
			s_path = ft_strjoin(s_path, "/");
			s_path = ft_strjoin(s_path, head->token);
			// printf("s_path is %s\n", s_path);
			if (!access(s_path, F_OK | R_OK)) {
				free(temp);
				// ft_free_arr(fst_cmd);
				return (s_path);
			}
			free(s_path);
			free(temp);
			env++;
		}
		// if (head->next_cmd->token != NULL)
		head = head->next_cmd;
		printf("\n\ntoken is %s\n\n", head->token);
	}
	// ft_print_arr(fst_cmd);
	// ft_free_arr(fst_cmd);
	// printf("command not found!\n");
	return NULL;
}

// saves the fd of all commands
void	ft_save_fd(t_shell *minishell)
{
	minishell->fd_in = dup(STDIN_FILENO);
	minishell->fd_out = dup(STDOUT_FILENO);
	// minishell->fd_err = dup(STDERR_FILENO);
	return ;
}

// executes the programme
int	ft_execve(t_shell *shell)
{
	int	fd[2];
	int	pid;
	int	status;

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
	return (fd[0]);
}

// // validates if has redirections
void	ft_has_redirections(t_shell *shell)
{
	int	fd[2];
	int	pid;
	int	status;
	t_cmds	*head;

	head = shell->cmds;
	head = head->next_cmd;
	int	fdd = open(shell->cmds->next_cmd->token, O_RDONLY);
	// int	fdd = open("infile" , O_RDONLY);
	if (fdd < 0) {
		perror ("fd opening error");
		exit (1);
	}
	if (strcmp(shell->cmds->token, "<") != 0)
		return ;
	if (pipe(fd) < 0) {
		perror ("pipe error on has_redirections\n");
		exit (2);
	}
	pid = fork();
	if (pid == 0) {
		// dup2(shell->fd_in, fdd);
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
void	ft_exec_cmd(t_shell *shell)
{
	ft_save_fd(shell);
	// if (shell->path != NULL && (strcmp(shell->cmds->token, "<") != 0))
	// 	ft_execve(shell);
	ft_has_redirections(shell);
	return ;
}

int main(int argc, char **argv, char **envp) 
{
	t_shell	*mini_shell;

	if (argc > 1)
		return (0);
	(void) argv;
	(void) argc;
	(void) envp;
	mini_shell = init_mini_shell(envp);
	while (1)
	{
		mini_shell->prompt = readline("minishell$: ");
		if (!mini_shell->prompt)
		{
			perror("prompt error");
			return (1);
		}
		mini_shell->tokens = ft_split(mini_shell->prompt, ' ');
		mini_shell->cmds = ft_init_cmds(mini_shell);
		add_history(mini_shell->prompt);
		ft_exec_cmd(mini_shell);
		ft_free_cmd(&mini_shell->cmds);
		// ft_free_arr(mini_shell->tokens);
		free(mini_shell->prompt);
	}
	ft_free_arr(mini_shell->envp);
	free(mini_shell);
	// ft_free_arr(paths);
	return (0);
}





// dup2(oldfd, newfd);
// the oldfd is copied into the newfd
