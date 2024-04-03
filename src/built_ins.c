#include "../includes/minishel.h"

// changes directory. Returns zero on success
// int	ft_chdir(char *dir, t_env *env)
// {
// 	;
// }


// frees t_cmds structure
void	ft_free_cmds(t_cmds *cmds)
{
	t_cmds	*node;
	t_cmds	*nxt_node;

	node = cmds;
	while (node) {
		nxt_node = node->next_cmd;
		free(node->token);
		free(node);
		node = nxt_node;
	}
	return ;
}

// finds the executable path in the operating system executables
// returns zero if success
int	ft_find_path(t_shell *shell)
{
	char	**splited;
	char	**tmp_split;
	char	*tmp;
	t_env	*env;
	int		out;
	t_cmds	*rmv;

	// if (shell->path)
	// 	return (1);
	rmv = shell->cmds;
	if (strcmp(rmv->token, "<") == 0)
		rmv = rmv->next_cmd->next_cmd;
	env = shell->env;
	while (env && strcmp(env->var_name, "PATH") != 0)
		env = env->next_node;
	splited = ft_split(env->var_value, ':');
	tmp_split = splited;
	out = 1;
	while (*tmp_split) {
		shell->path = ft_strjoin(*tmp_split, "/");
		tmp = shell->path;
		shell->path = ft_strjoin(tmp, rmv->token);
		if (!access(shell->path, F_OK)) {
			free(tmp);
			out = 0;
			break ;
		}
		free(tmp);
		free(shell->path);
		shell->path = NULL;
		tmp_split++;
	}
	ft_free_arr(splited);
	return (out);
}

// validates if token node has any kind of redirection
int	ft_contais_redir(char *cmd)
{
	if ((strcmp(cmd, "<") == 0) || (strcmp(cmd, "<<") == 0) || (strcmp(cmd, ">") == 0) || (strcmp(cmd, ">>") == 0))
		return (1);
	return (0);
}


// redirects input
// returns zero on success
void	ft_redir_input(t_shell *shell)
{
	t_cmds	*head;
	t_cmds	*next;
	
	head = shell->cmds;
	next = head->next_cmd;
	shell->cmds = shell->cmds->next_cmd->next_cmd;
	free(head->token);
	free(head);
	shell->fd_in = open(next->token, O_RDONLY);
	if (shell->fd_in < 0) {
		perror (next->token);
		return ;
	}
	free(next->token);
	free(next);
	return ;
}

// deals with redirections
// returns zero on success
int	ft_deal_redir(t_shell *shell)
{
	if (strcmp(shell->cmds->token, "<") == 0)
		ft_redir_input(shell);
	return (0);
}

// advances on commands according to redirections
// returns zero if success
// char	**ft_2d_arr(t_shell *shell)
// int	ft_2d_arr(t_shell *shell)
// {
// 	int		i;
// 	t_cmds	*head;
// 	int		path;

// 	if (ft_contais_redir(shell->cmds->token))
// 		if (ft_deal_redir(shell))
// 			return (1);
// 	if (ft_find_path(shell))
// 		return (2);
// 	head = shell->cmds;
// 	i = 0;
// 	while (head && !ft_contais_redir(head->token)) {
// 		i++;
// 		head = head->next_cmd;
// 	}
// 	shell->tokens = calloc(sizeof(char *), i + 1);
// 	i = 0;
// 	head = shell->cmds;
// 	while (shell->cmds && !ft_contais_redir(shell->cmds->token)) {
// 		head = shell->cmds;
// 		shell->tokens[i++] = strdup(head->token);
// 		shell->cmds = shell->cmds->next_cmd;
// 		free(head->token);
// 		free(head);
// 	}
// 	shell->tokens[i] = NULL;
// 	return (0);
// }

int	ft_2d_arr(t_shell *shell)
{
	int		i;
	t_cmds	*head;

	head = shell->cmds;
	i = 0;
	while (head) {
		i++;
		head = head->next_cmd;
	}
	shell->tokens = calloc(sizeof(char *), i + 2);
	shell->tokens[0] = strdup(shell->path);
	i = 1;
	head = shell->cmds;
	while (shell->cmds) {
		head = shell->cmds;
		shell->tokens[i] = strdup(head->token);
		shell->cmds = shell->cmds->next_cmd;
		free(head->token);
		free(head);
		i++;
	}
	shell->tokens[i] = NULL;
	return (0);
}

int	ft_2d_arr_new(t_shell *shell)
{
	int		i;
	t_cmds	*head;

	head = shell->cmds;
	i = 0;
	while (head) {
		if (strcmp(head->token, "<") == 0) {
			close (shell->fd_in);
			if (head->next_cmd)
				head = head->next_cmd;
			else {
				perror ("syntax error near unexected token 'newline'!");
				return (1);
			}
			shell->fd_in = open(head->token, O_RDONLY);
			if (shell->fd_in < 0) {
				perror (head->token);
				return (1);
			}
		}
		else
			i++;
		head = head->next_cmd;
	}
	shell->tokens = calloc(sizeof(char *), i + 1);
	// i = 1;
	i = 0;
	head = shell->cmds;
	while (head) {
		if (strcmp(head->token, "<") != 0) {
			shell->tokens[i++] = strdup(head->token);
			// i++;
		}
		else
			if (head->next_cmd)
				head = head->next_cmd;
		head = head->next_cmd;
	}
	shell->tokens[i] = NULL;
	return (0);
}

void	ft_simple_redirect(t_shell *shell)
{
	t_cmds	*head;

	head = shell->cmds;
	if (head && strcmp(head->token, "<") == 0) {
		shell->fd_in = open(head->next_cmd->token, O_RDONLY);
		if (shell->fd_in < 0) {
			perror (head->next_cmd->token);
			exit (1);
		}
		shell->cmds = shell->cmds->next_cmd;
		free(head->token);
		free(head);
		head = shell->cmds;
		shell->cmds = shell->cmds->next_cmd;
		free(head->token);
		free(head);
	}
}

void	ft_simple_redirect_new(t_shell *shell)
{
	t_cmds	*head;
	t_cmds	*current;

	ft_print_cmds(shell->cmds);
	current = shell->cmds;
	while (current) {
		head = current;
		if (strcmp(head->token, "<") == 0) {
			shell->fd_in = open(head->next_cmd->token, O_RDONLY);
			if (shell->fd_in < 0) {
				perror (head->next_cmd->token);
				exit (1);
			}
			current->next_cmd = current->next_cmd->next_cmd;
			current = current->next_cmd;
			if (strcmp(shell->cmds->token, "<") == 0)
				shell->cmds = current->next_cmd->next_cmd;
			free(head->token);
			free(head);
		}
		current = current->next_cmd;
	}
	ft_print_cmds(shell->cmds);
}

// executes the executables with execve
// void	ft_execve(t_shell *shell, char *token)
void	ft_execve_(t_shell *shell)
{
	int	fd[2];
	int	pid;

	if (ft_2d_arr_new(shell))
		return ;
	// ft_print_arr(shell->tokens);
	// printf("here\n");
	// ft_print_arr(shell->tokens);
	if (pipe(fd) < 0) {
		perror ("pipe error on ft_execve!\n");
		exit (1);
	}
	pid = fork();
	if (pid < 0) {
		perror ("fork error on ft_execve\n");
		exit (2);
	}
	if (pid == 0) {
		dup2(shell->fd_in, STDIN_FILENO);
		dup2(shell->fd_out, fd[1]);
		execve(shell->path, shell->tokens, NULL);
		// execve(shell->path, (char *[]) {shell->path, NULL}, NULL);
		// if (shell->tokens[1])
		// 	execve(shell->path, shell->tokens, NULL);
		// 	// execve(shell->path, (char *[]) {shell->path, "infile", NULL}, NULL);
		// 	// execve(shell->path, (char *[]) {shell->path, shell->cmds->token, NULL}, NULL);
		// else
		// 	execve(shell->path, (char *[]) {shell->path, NULL}, NULL);
	}
	else {
		close (fd[0]);
		close (fd[1]);
		// if (!shell->cmds)
		// 	printf("No more commands!\n\n");
		waitpid(pid, NULL, 0);
		// dup2(shell->fd_in, STDIN_FILENO);
		// dup2(shell->fd_out, STDOUT_FILENO);
		// close(shell->fd_in);
		// close(shell->fd_out);
	}
	return ;
}

